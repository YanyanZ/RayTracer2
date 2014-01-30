# include <scene/Tracer.hpp>

using namespace Engine;

Tracer::Tracer (Scene * sc)
: s (sc), nbThrowRay (0)
{
}

Tracer::~Tracer ()
{
    if (map)
        delete map;

    if (s)
        delete s;
}

void Tracer::saveScene(std::string output)
{
    std::ofstream of(output.c_str());
    int i, j, k;
    int MaxVal = 255;

    of << "P6" << std::endl;
    of << width << " " << height << std::endl;
    of << MaxVal << std::endl;

    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            for (k = 0; k < 3; k++)
                of << map[((height - i - 1) * width + j) * 3 + k];

    of.close ();
}

void Tracer::setPixel (int x, int y, double c[3])
{
    map[x * 3 * width + y * 3] = static_cast<unsigned char>(c[0] * 255);
    map[x * 3 * width + y * 3 + 1] = static_cast<unsigned char>(c[1] * 255);
    map[x * 3 * width + y * 3 + 2] = static_cast<unsigned char>(c[2] * 255);
}

void Tracer::getPixel (int x, int y, double c[3])
{
    c[0] = map[x * 3 * width + y * 3];
    c[1] = map[x * 3 * width + y * 3 + 1];
    c[2] = map[x * 3 * width + y * 3 + 2];
}

void Tracer::createScene(void)
{
    int i, j;
    double color[3];

    s->getAmbiant(aLight);

    memcpy(cBackground, s->getBackground(), 3 * sizeof(double));

    width = s->getOutputWidth();
    height = s->getOutputHeight();

    pwidth = (s->getCamera())->getSProjection();
    pheight = pwidth * height/width;

    pasy = static_cast<double>(pwidth) / static_cast<double>(width);
    pasx = static_cast<double>(pheight) / static_cast<double>(height);

    map = (unsigned char *) malloc (3 * width * height * sizeof (unsigned char));

    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
        {
            throwRays(i, j, color);
            map[i * 3 * width + j * 3] = (unsigned char) (color[0] * 255);
            map[i * 3 * width + j * 3 + 1] = (unsigned char) (color[1] * 255);
            map[i * 3 * width + j * 3 + 2] = (unsigned char) (color[2] * 255);
        }
}

void Tracer::throwRays(int i, int j, double c[3])
{
    double ctmp[3];
    int ph[2];
    int pg[2];
    double ch[3];
    double cg[3];
    double diff1, diff2;
    double x, y, k;
    int aa = s->getAntialiasing ();
    double aa_threshold = s->getAAThreshold ();
    Ray* r = new Ray();
    Ray* r2 = new Ray();

    y = pasy * (static_cast<double>(j)) - pwidth / 2.0;
    x = pasx * (static_cast<double>(i)) - pheight / 2.0;
    initRay(x, y, r);
    (s->getCamera())->rScene(r, r2);

    c[0] = 0;
    c[1] = 0;
    c[2] = 0;

    throwRay(r2, s->getMaxTraceLevel(), c);

    if (aa > 1)
    {
        if (i == 0 && j == 0)
        {
            ph[0] = 0;
            pg[0] = 0;
            ph[1] = 0;
            pg[1] = 0;
        }
        if (i == 0 && j > 0)
        {
            ph[0] = 0;
            ph[1] = j;
            pg[0] = 0;
            pg[1] = j - 1;
        }

        if (i > 0 && j == 0)
        {
            ph[0] = i - 1;
            ph[1] = 0;
            pg[0] = i;
            pg[1] = 0;
        }

        if (i > 0 && j > 0)
        {
            ph[0] = i - 1;
            ph[1] = j;
            pg[0] = i;
            pg[1] = j - 1;
        }

        getPixel(ph[0], ph[1], ch);
        getPixel(pg[0], pg[1], cg);

        diff1 = fabs (c[0] - ch[0]) +
            fabs (c[1] - ch[1]) +
            fabs (c[2] - ch[2]);
        diff2 = fabs (c[0] - cg[0]) +
            fabs (c[1] - cg[1]) +
            fabs (c[2] - cg[2]);

        k=1;
        while  (k <= aa &&
                (diff1 > aa_threshold || diff2 > aa_threshold))
        {
            y = pasy * (static_cast<double>(j) -
                    static_cast<double>(random()) /
                    static_cast<double>(MAXINT)) - pwidth / 2.0;

            x = pasx * (static_cast<double>(i) -
                    static_cast<double>(random()) /
                    static_cast<double>(MAXINT)) - pheight / 2.0;

            initRay(x, y, r);
            (s->getCamera())->rScene(r, r2);
            throwRay(r2, s->getMaxTraceLevel(), ctmp);
            for(int t = 0; t < 3; t++)
                c[t] = ((static_cast<double>(aa) - 1.0) *
                        c[t] + ctmp[t]) / static_cast<double>(aa);

            diff1 = fabs (c[0] - ch[0]) +
                fabs (c[1] - ch[1]) +
                fabs (c[2] - ch[2]);
            diff2 = fabs (c[0] - cg[0]) +
                fabs (c[1] - cg[1]) +
                fabs (c[2] - cg[2]);

            k++;
        }
    }

    /* clamping */
    for (int k = 0; k < 3; k++)
        if (c[k] > 1.0)
            c[k] = 1.0;
}

void Tracer::initRay(double x, double y, Ray* r)
{
    Camera* c = s->getCamera();

    r->setIn(false);

    if (c->getTProjection() == Camera::PERSPECTIVE)
    {
        double dir[4] = {x, y, c->getFocal(), 0};;
        double pos[4] = {0, 0, 0, 1};

        r->setOrigin(pos);
        r->setDirection(dir);
    }
    else
    {
        double dir[4] = {0, 0, 1, 0};
        double pos[4] = {x , y, 0, 1};

        r->setOrigin(pos);
        r->setDirection(dir);
    }
}

void Tracer::throwRay(Ray* r, int deep, double c[3])
{
    double d;
    Object *o = nullptr;
    double hit[4] = {0, 0, 0, 0};
    double normal[4] = {0, 0, 0, 0};
    double cDirect[3] = {0, 0, 0};
    double cAmbient[3] = {0, 0, 0};
    double cReflect[3] = {0, 0, 0};
    double cSend[3] = {0, 0, 0};

    if (deep > 0)
    {
        nbThrowRay++;
        d = evalHit(r, hit, &o);

        if (d != MAXDOUBLE)
        {
            o->normal(hit, r, normal);

            evalDirectRadiance(r, o, hit, normal, cDirect);
            evalAmbiantRadiance(o, hit, cAmbient);
            evalReflectRadiance(r, o, hit, normal, deep, cReflect);
            evalSendRadiance(r, o, hit, normal, deep, cSend);

            for (int i = 0; i < 3; i++)
                c[i] += cDirect[i] + o->getRhoA() * cAmbient[i] +
                    o->getRhoR() * cReflect[i] + o->getRhoT() * cSend[i];

        }
        else
        {
            c[0] += cBackground[0];
            c[1] += cBackground[1];
            c[2] += cBackground[2];
        }
    }
}

double Tracer::evalHit(Ray* r, double hit[], Object** o)
{
    double d1, d2;
    Object *o2;
    double i2[4] = {0, 0, 0, 0};

    *o = s->getObject(0);
    d1 = (*o)->hit(r, hit);

    for (int i = 1; i < s->getNbObjects(); i++)
    {
        o2 = s->getObject(i);
        d2 = o2->hit(r, i2);
        if (d2 < d1)
        {
            d1 = d2;
            *o = s->getObject (i);
            memcpy(hit, i2, 4 * sizeof(double));
        }
    }

    return d1;
}

void Tracer::evalDirectRadiance(Ray* r, Object* o,
        double hit[4],
        double normal[4],
        double c[3])
{
    double c2[3] = {0, 0, 0};

    c[0] = 0;
    c[1] = 0;
    c[2] = 0;

    for (int i = 0; i < s->getNbPoints(); i++)
        for(int j = 0; j < s->getNbShadowRay(); j++)
            if (s->isPointRadiance(hit, i))
            {
                (s->getPoint(i))->getShiness(r, hit, normal, o , c2);
                c[0] += c2[0] / s->getNbShadowRay();
                c[1] += c2[1] / s->getNbShadowRay();
                c[2] += c2[2] / s->getNbShadowRay();
            }

    for (int i = 0; i < s->getNbDirectionals(); i++)
        for(int j = 0; j < s->getNbShadowRay(); j++)
            if (s->isDirectionalRadiance(hit, i))
            {
                s->getDirectional(i)->getShiness(r, hit, normal, o , c2);
                c[0] += c2[0] / s->getNbShadowRay();
                c[1] += c2[1] / s->getNbShadowRay();
                c[2] += c2[2] / s->getNbShadowRay();
            }
}

void Tracer::evalReflectRadiance(Ray* r, Object* o,
        double hit[4],
        double normal[4],
        int deep,
        double c[3])
{
    Ray* rRay = new Ray();

    c[0] = 0;
    c[1] = 0;
    c[2] = 0;

    if (o->rRay(r, hit, normal, rRay))
        throwRay(rRay, deep - 1, c);

    delete rRay;
}

void Tracer::evalSendRadiance (Ray* r, Object* o,
        double hit[4],
        double normal[4],
        int deep,
        double c[4])
{
    Ray* sRay = new Ray();

    c[0] = 0;
    c[1] = 0;
    c[2] = 0;

    if (o->tRay(r, hit, normal, sRay))
        throwRay(sRay, deep - 1, c);

    delete sRay;
}

void Tracer::evalAmbiantRadiance (Object* o,
        double p[3],
        double c[3])
{
    double c2[3] = {0, 0, 0};

    c[0] = 0;
    c[1] = 0;
    c[2] = 0;

    o->getColor(p, c2);
    for (int i = 0; i < 3; i++)
        c[i] = c2[i] * aLight[i];
}
