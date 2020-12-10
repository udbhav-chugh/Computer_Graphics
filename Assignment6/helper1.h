//class to store vector and define operations on vector
class helpClass{
public:
    double x;
    double y;
    double z;
    //constructor
    helpClass() : x(double(0)), y(double(0)), z(double(0)) {
    }
    helpClass(double xVal) : x(xVal), y(xVal), z(xVal) {
    }
    helpClass(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {
    }
    // spheres normalisation
    helpClass& reduceNorm(){
        double normalVal = x*x + y*y + z*z;
        if (normalVal > 1){
            double inverseNormalVal = 1 / sqrt(normalVal);
            x *= inverseNormalVal, y *= inverseNormalVal, z *= inverseNormalVal;
        }
        return *this;
    }
    // operators.
    double dot(const helpClass &v) const { 
        return x * v.x + y * v.y + z * v.z; 
    }
    helpClass operator - (const helpClass &v) const { 
        return helpClass(x - v.x, y - v.y, z - v.z); 
    }
    helpClass operator + (const helpClass &v) const { 
        return helpClass(x + v.x, y + v.y, z + v.z); 
    }
    helpClass& operator += (const helpClass &v) { 
        x += v.x;
        y += v.y;
        z += v.z; 
        return *this; 
    }
    helpClass& operator *= (const helpClass &v) { 
        x *= v.x;
        y *= v.y;
        z *= v.z; 
        return *this; 
    }
    helpClass operator - () const { 
        return helpClass(-x, -y, -z); 
    }
    helpClass operator * (const double &f) const { 
        return helpClass(x * f, y * f, z * f); 
    }
    helpClass operator * (const helpClass &v) const { 
        return helpClass(x * v.x, y * v.y, z * v.z); 
    }   
};

//class to store sphere information for ray tracing
class SphereClass{
public:
    // SphereClass variables.
    helpClass center;                         
    double radius;
    double radiusSquare;                      
    double transp;
    double reflection;             
    helpClass planeCol;
    helpClass emiCol;    

    // SphereClass constructor.
    SphereClass(const helpClass &c, const double &r, const helpClass &sc, const double &refl = 0, const double &transp = 0, const helpClass &ec = 0) : 
        center(c), radius(r), planeCol(sc), reflection(refl),transp(transp), emiCol(ec), radiusSquare(r * r){
    }

    // compute a ray-sphere intersection
    bool intersect(const helpClass &rayorig, const helpClass &directionOfRay, double *t0 = NULL, double *t1 = NULL) const
    {
        helpClass l = center - rayorig;
        double tempValue = l.dot(directionOfRay);
        if (tempValue < 0) return false;
        double d2 = l.dot(l) - (tempValue * tempValue);
        if (d2 > radiusSquare) return false;
        double thc = sqrt(radiusSquare - d2);
        if (t0 != NULL && t1 != NULL) {
            *t0 = tempValue - thc;
            *t1 = tempValue + thc;
        }
        return true;
    }
};

std::vector<SphereClass *> spheresVec;

// This is the main rayTrace function.
helpClass rayTraceHelper(const helpClass &rayorig, const helpClass &directionOfRay, const std::vector<SphereClass *> &spheresVec, const int &depth){
    double tnear = INFINITY;
    const SphereClass *sphere = NULL;
    // Try to find intersection of this directionOfRay with the spheresVec in the scene
    for (unsigned i = 0; i < spheresVec.size(); ++i){
        double t0 = INFINITY, t1 = INFINITY;
        if (spheresVec[i]->intersect(rayorig, directionOfRay, &t0, &t1)){
            if (t0 < 0) t0 = t1;
            if (t0 < tnear) {
                tnear = t0;
                sphere = spheresVec[i];
            }
        }
    }
    if (!sphere) return helpClass(.5); // Grey background color.
    helpClass planeCol = 0; 
    helpClass phit = rayorig + (directionOfRay * tnear);
    helpClass nhit = phit - sphere->center; 
    if (directionOfRay.dot(nhit) > 0) nhit = -nhit;
    nhit.reduceNorm();
    double bias = 1e-5;

    if ((sphere->transp > 0 || sphere->reflection > 0) && depth < 3){
        double IdotN = directionOfRay.dot(nhit); 
        double facingratio = std::max(double(0), -IdotN);
		double val1 = pow(1 - facingratio, 3);
		double val2 = 1;
        double fresneleffect = val2 * 0.1 + val1 * (double(1) - 0.1);
        helpClass refldir = directionOfRay - nhit * 2 * directionOfRay.dot(nhit);
        helpClass reflection = rayTraceHelper(phit + (nhit * bias), refldir, spheresVec, depth + 1);
        helpClass refraction = 0;
        if (sphere->transp){
            double ior = 1.2, eta = 1 / ior;
            double k = 1 - eta * eta * (1 - IdotN * IdotN);
            helpClass refrdir = directionOfRay * eta - nhit * (eta *  IdotN + sqrt(k));
            refraction = rayTraceHelper(phit - nhit * bias, refrdir, spheresVec, depth + 1);
        }
        planeCol = (reflection * fresneleffect + refraction * (1 - fresneleffect) * sphere->transp) * sphere->planeCol;
    }
    else{
        double shadow = 1.0;
        for (unsigned i = 0; i < spheresVec.size(); ++i){
            if (spheresVec[i]->emiCol.x > 0) {
                helpClass transmission = 1.0;
                helpClass lightDirection = spheresVec[i]->center - phit;
                lightDirection.reduceNorm();
                double light_angle = (acos(directionOfRay.dot(lightDirection)) / ( sqrt(directionOfRay.dot(directionOfRay)) * sqrt(lightDirection.dot(lightDirection))));
                double light_incidence = sin(light_angle);
                for (unsigned j = 0; j < spheresVec.size(); ++j) {
                    if (i != j) {
                        double t0, t1;
                        if (spheresVec[j]->intersect(phit + (nhit * bias), lightDirection, &t0, &t1)) {
                            shadow = std::max(0.0, shadow - (1.0 - spheresVec[j]->transp));
                            transmission = transmission * spheresVec[j]->planeCol * shadow;
                        }
                    }
                }
                planeCol += sphere->planeCol * transmission * 
                    std::max(double(0), nhit.dot(lightDirection)) * spheresVec[i]->emiCol;
            }
        }
    }
    return planeCol + sphere->emiCol;
}

// Main rendering function.
helpClass *image = new helpClass[480 * 480];
static helpClass cam_pos = helpClass(0);
void renderSpheres(const std::vector<SphereClass *> &spheresVec){
    helpClass *pixVal = image;
    double oneByWidth = 1 / double(480);
    double oneByHeight = 1 / double(480);
    double fieldOfView = 30;
    double aspectratio = double(480) / double(480);
    double angle = tan(M_PI * 0.5 * fieldOfView / double(180));
    // Trace rays
    for (GLuint y = 0; y < 480; ++y){
        for (GLuint x = 0; x < 480; ++x, ++pixVal){
            double xVal = (2 * ((x + 0.5) * oneByWidth) - 1) * angle * aspectratio;
            double yVal = (1 - 2 * ((y + 0.5) * oneByHeight)) * angle;
            helpClass directionOfRay(xVal, yVal, -1);
            directionOfRay.reduceNorm();
            *pixVal = rayTraceHelper(cam_pos, directionOfRay, spheresVec, 0);
        }
    }
}