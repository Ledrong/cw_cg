#include "usagefacade.hpp"

#include "QDebug"
#include "QPen"

#include <limits>

#include "math.h"
#include "config.hpp"

UsageFacade::UsageFacade() { drawer = new Drawer; }

void UsageFacade::setCellScene(size_t width_, size_t height_)
{
    if (scene)
        delete scene;

    scene = new CellScene(width_, height_);
}

void UsageFacade::changeCellScene(size_t newWidth, size_t newheight)
{
    scene->changeSize(newWidth, newheight);
}

bool UsageFacade::isSceneSet() { return scene; }

QGraphicsScene *UsageFacade::drawScene(QRectF rect)
{
    QGraphicsScene *retScene = nullptr;
    if (isSceneSet())
        retScene = drawer->drawScene(scene, rect);

    return retScene;
}

QGraphicsScene *UsageFacade::moveUpScene(double value, QRectF rect)
{
    scene->moveUp(value);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::moveDownScene(double value, QRectF rect)
{
    scene->moveDown(value);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::moveRightScene(double value, QRectF rect)
{
    scene->moveRight(value);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::moveLeftScene(double value, QRectF rect)
{
    scene->moveLeft(value);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::scaleScene(double value, QRectF rect)
{
    scene->scale(value);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::rotateXScene(double angle, QRectF rect)
{
    scene->rotateX(angle);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::rotateYScene(double angle, QRectF rect)
{
    scene->rotateY(angle);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::rotateZScene(double angle, QRectF rect)
{
    scene->rotateZ(angle);

    return drawScene(rect);
}

QGraphicsScene *UsageFacade::toCenter(QRectF rect)
{
    scene->toCenter();

    return drawScene(rect);
}

CellScene *UsageFacade::getScene() { return scene; }

void UsageFacade::addQuad(std::vector<Vertex> &vertices, std::vector<Facet> &facets,
    int x1, int y1, int z1, int x2, int y2, int z2,
    int x3, int y3, int z3, int x4, int y4, int z4)
{
    Dot3D dot;
    std::vector<size_t> vec;

    size_t size = facets.size();

    dot = Dot3D(x1, y1, z1);
    vec = {size, size + 1};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x2, y2, z2);
    vec = {size};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x3, y3, z3);
    vec = {size, size + 1};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x4, y4, z4);
    vec = {size + 1};
    vertices.push_back(Vertex(dot, vec));

    size = vertices.size();
    vec = {size - 4, size - 3, size - 2};
    facets.push_back(vec);
    vec = {size - 4, size - 2, size - 1};
    facets.push_back(vec);
}

void UsageFacade::addTriangle(std::vector<Vertex> &vertices, std::vector<Facet> &facets,
    int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3)
{
    Dot3D dot;
    std::vector<size_t> vec;

    size_t size = facets.size();

    dot = Dot3D(x1, y1, z1);
    vec = {size};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x2, y2, z2);
    vec = {size};
    vertices.push_back(Vertex(dot, vec));

    dot = Dot3D(x3, y3, z3);
    vec = {size};
    vertices.push_back(Vertex(dot, vec));

    size = vertices.size();
    vec = {size - 3, size - 2, size - 1};
    facets.push_back(vec);
}

void UsageFacade::addIlluminant(int xAngle, int yAngle)
{
    Eigen::Matrix4f transMat;
    double radianXAngle = (double) xAngle * M_PI / 180.0;
    double radianYAngle = (double) yAngle * M_PI / 180.0;

    transMat << 1,          0,          0,               0,
               0, cos(radianXAngle), -sin(radianXAngle), 0,
               0, sin(radianXAngle),  cos(radianXAngle), 0,
               0,           0,          0,               1;

    Eigen::Matrix4f prodMat;
    prodMat << cos(radianYAngle), 0, sin(radianYAngle), 0,
                0,                1,    0,              0,
              -sin(radianYAngle), 0, cos(radianYAngle), 0,
                0,                0,    0,              1;

    transMat *= prodMat;

    Illuminant illum(transMat);
    illum.setAngles(xAngle, yAngle);
    scene->addIlluminant(illum);
}

void Drawer::specBorderPut(int x, int y, double z)
{
    if (x < 0 || x >= (int) depthBuffer.size() || \
        y < 0 || y >= (int) depthBuffer.at(0).size())
        return;
    if (std::fabs(z - depthBuffer.at(x).at(y)) < 1 || z > depthBuffer.at(x).at(y))
        frameBuffer.at(x).at(y) = 3;
}

void Drawer::DDABordersForPolygon(
    int xStart, int yStart, double zStart, int xEnd, int yEnd, double zEnd)
{
    if (xStart == xEnd && yStart == yEnd)
    {
        specBorderPut(xStart, yStart, zStart);
        return;
    }

    double deltaX = xEnd - xStart;
    double deltaY = yEnd - yStart;
    double deltaZ = zEnd - zStart;

    int trX = abs(deltaX);
    int trY = abs(deltaY);

    int length;
    if (trX > trY)
        length = trX;
    else
        length = trY;

    deltaX /= length;
    deltaY /= length;
    deltaZ /= length;

    double curX = xStart;
    double curY = yStart;
    double curZ = zStart;

    for (int i = 0; i < length; i++)
    {
        specBorderPut(round(curX), round(curY), curZ);
        curX += deltaX;
        curY += deltaY;
        curZ += deltaZ;
    }
}

void Drawer::interpolateRowIntoShadowMap(
    std::vector<std::vector<double>> *map, int xA, int xB, double zA, double zB, int curY)
{
    for (int curX = xA; curX <= xB; curX++)
    {
        double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);
        if (curX >= (int) map->size() || curX < 0 || curY >= (int) map->at(0).size() ||
            curY < 0)
            continue;

        if (curZ > map->at(curX).at(curY))
            map->at(curX).at(curY) = curZ;
    }
}

void Drawer::shadowMapForModel(std::vector<Facet> &facets, std::vector<Vertex> &vertices,
    Eigen::Matrix4f &transMat, Illuminant *illum, size_t bufWidth, size_t bufHeight)
{
    std::array<Dot3D, 3> dotsArr;
    Eigen::Matrix4f toCenter;

    toCenter << 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -X_CENTER, -Y_CENTER, -PLATE_Z - 5, 1;

    Eigen::Matrix4f backToStart;

    backToStart << 1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   X_CENTER, Y_CENTER, PLATE_Z + 5, 1;

    std::vector<std::vector<double>> *shadowMap = &illum->getShadowMap();
    Eigen::Matrix4f illumMat = illum->getTransMat();

    Eigen::Matrix4f dotTransMat = toCenter * transMat * illumMat * backToStart;

    for (size_t curFaceNum = 0; curFaceNum < facets.size(); curFaceNum++)
    {
        Eigen::MatrixXf coordinatesVec(3, 4);

        std::vector<size_t> curDots = facets.at(curFaceNum).getUsedVertices();
        dotsArr[0] = vertices.at(curDots.at(0)).getPosition();
        dotsArr[1] = vertices.at(curDots.at(1)).getPosition();
        dotsArr[2] = vertices.at(curDots.at(2)).getPosition();

        coordinatesVec <<
            dotsArr[0].getXCoordinate(), dotsArr[0].getYCoordinate(), dotsArr[0].getZCoordinate(), 1,
            dotsArr[1].getXCoordinate(), dotsArr[1].getYCoordinate(), dotsArr[1].getZCoordinate(), 1,
            dotsArr[2].getXCoordinate(), dotsArr[2].getYCoordinate(), dotsArr[2].getZCoordinate(), 1;

        coordinatesVec *= dotTransMat;
        dotsArr[0] =
            Dot3D(coordinatesVec(0, 0), coordinatesVec(0, 1), coordinatesVec(0, 2));
        dotsArr[1] =
            Dot3D(coordinatesVec(1, 0), coordinatesVec(1, 1), coordinatesVec(1, 2));
        dotsArr[2] =
            Dot3D(coordinatesVec(2, 0), coordinatesVec(2, 1), coordinatesVec(2, 2));

        if (dotsArr[0].getYCoordinate() > dotsArr[1].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[1]);
        if (dotsArr[0].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[2]);
        if (dotsArr[1].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[1], dotsArr[2]);

        int x1 = round(dotsArr[0].getXCoordinate());
        int x2 = round(dotsArr[1].getXCoordinate());
        int x3 = round(dotsArr[2].getXCoordinate());

        double z1 = dotsArr[0].getZCoordinate();
        double z2 = dotsArr[1].getZCoordinate();
        double z3 = dotsArr[2].getZCoordinate();

        int y1 = round(dotsArr[0].getYCoordinate());
        int y2 = round(dotsArr[1].getYCoordinate());
        int y3 = round(dotsArr[2].getYCoordinate());

//#pragma omp parallel for
        for (int curY = (y1 < 0) ? 0 : y1;
             curY < ((y2 >= (int) bufHeight) ? (int) bufHeight - 1 : y2); curY++)
        {
            double aInc = 0;
            if (y1 != y2)
                aInc = (double) (curY - y1) / (y2 - y1);

            double bInc = 0;
            if (y1 != y3)
                bInc = (double) (curY - y1) / (y3 - y1);

            int xA = round(x1 + (x2 - x1) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z1 + (z2 - z1) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            if (xA < 0)
                xA = 0;
            if (xB >= (int) bufWidth)
                xB = (int) bufWidth - 1;

            interpolateRowIntoShadowMap(shadowMap, xA, xB, zA, zB, curY);
        }

//#pragma omp parallel for
        for (int curY = (y2 < 0) ? 0 : y2;
             curY <= ((y3 >= (int) bufHeight) ? (int) bufHeight - 1 : y3); curY++)
        {
            double aInc = 0;
            if (y2 != y3)
                aInc = (double) (curY - y2) / (y3 - y2);

            double bInc = 0;
            if (y1 != y3)
                bInc = (double) (curY - y1) / (y3 - y1);

            int xA = round(x2 + (x3 - x2) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z2 + (z3 - z2) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            if (xA < 0)
                xA = 0;
            if (xB >= (int) bufWidth)
                xB = (int) bufWidth - 1;

            interpolateRowIntoShadowMap(shadowMap, xA, xB, zA, zB, curY);
        }
    }
}

void Drawer::zBufForModel(std::vector<Facet> &facets, std::vector<Vertex> &vertices,
    Eigen::Matrix4f &transMat, size_t color, CellScene *scene, size_t bufWidth,
    size_t bufHeight)
{
    std::array<Dot3D, 3> dotsArr;
    Eigen::Matrix4f toCenter;

    toCenter << 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -X_CENTER, -Y_CENTER, -PLATE_Z - 5, 1;

    Eigen::Matrix4f backToStart;

    backToStart << 1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   X_CENTER, Y_CENTER, PLATE_Z + 5, 1;

    Eigen::Matrix4f dotTransMat;
    dotTransMat = toCenter * transMat * backToStart;
    std::vector<Eigen::Matrix4f> illumDotMatrices;

    for (size_t i = 0; i < scene->getIllumNum(); i++)
        illumDotMatrices.push_back(
            toCenter * scene->getIlluminant(i).getTransMat() * backToStart);

    for (size_t curFaceNum = 0; curFaceNum < facets.size(); curFaceNum++)
    {
        Eigen::MatrixXf coordinatesVec(3, 4);

        std::vector<size_t> curDots = facets.at(curFaceNum).getUsedVertices();
        dotsArr[0] = vertices.at(curDots.at(0)).getPosition();
        dotsArr[1] = vertices.at(curDots.at(1)).getPosition();
        dotsArr[2] = vertices.at(curDots.at(2)).getPosition();

        coordinatesVec <<
            dotsArr[0].getXCoordinate(), dotsArr[0].getYCoordinate(), dotsArr[0].getZCoordinate(), 1,
            dotsArr[1].getXCoordinate(), dotsArr[1].getYCoordinate(), dotsArr[1].getZCoordinate(), 1,
            dotsArr[2].getXCoordinate(), dotsArr[2].getYCoordinate(), dotsArr[2].getZCoordinate(), 1;

        coordinatesVec *= dotTransMat;

        dotsArr[0] =
            Dot3D(coordinatesVec(0, 0), coordinatesVec(0, 1), coordinatesVec(0, 2));
        dotsArr[1] =
            Dot3D(coordinatesVec(1, 0), coordinatesVec(1, 1), coordinatesVec(1, 2));
        dotsArr[2] =
            Dot3D(coordinatesVec(2, 0), coordinatesVec(2, 1), coordinatesVec(2, 2));

        if (dotsArr[0].getYCoordinate() > dotsArr[1].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[1]);
        if (dotsArr[0].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[0], dotsArr[2]);
        if (dotsArr[1].getYCoordinate() > dotsArr[2].getYCoordinate())
            std::swap(dotsArr[1], dotsArr[2]);

        int x1 = round(dotsArr[0].getXCoordinate());
        int x2 = round(dotsArr[1].getXCoordinate());
        int x3 = round(dotsArr[2].getXCoordinate());

        double z1 = dotsArr[0].getZCoordinate();
        double z2 = dotsArr[1].getZCoordinate();
        double z3 = dotsArr[2].getZCoordinate();

        int y1 = round(dotsArr[0].getYCoordinate());
        int y2 = round(dotsArr[1].getYCoordinate());
        int y3 = round(dotsArr[2].getYCoordinate());

//#pragma omp parallel for
        for (int curY = (y1 < 0) ? 0 : y1;
             curY < ((y2 >= (int) bufHeight) ? (int) bufHeight - 1 : y2); curY++)
        {
            double aInc = 0;
            if (y1 != y2)
                aInc = (double) (curY - y1) / (y2 - y1);

            double bInc = 0;
            if (y1 != y3)
                bInc = (double) (curY - y1) / (y3 - y1);

            int xA = round(x1 + (x2 - x1) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z1 + (z2 - z1) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            if (xA < 0)
                xA = 0;
            if (xB >= (int) bufWidth)
                xB = (int) bufWidth - 1;

            for (int curX = xA; curX <= xB; curX++)
            {
                double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);

                if (curZ >= depthBuffer.at(curX).at(curY))
                {
                    short visible = 0;
                    Eigen::MatrixXf newCoordinates(1, 4);

                    for (size_t i = 0; i < scene->getIllumNum() && !visible; i++)
                    {
                        newCoordinates << curX, curY, curZ, 1;

                        newCoordinates *= illumDotMatrices.at(i);
                        std::vector<std::vector<double>> *shadowMap =
                            &scene->getIlluminant(i).getShadowMap();

                        int x = round(newCoordinates(0, 0));
                        int y = round(newCoordinates(0, 1));

                        if (x < (int) shadowMap->size() && x >= 0 &&
                            y < (int) shadowMap->at(0).size() && y >= 0 &&
                            std::fabs(shadowMap->at(x).at(y) - newCoordinates(0, 2)) < 2)
                            visible = 1;
                    }
                    depthBuffer.at(curX).at(curY) = curZ;
                    if (scene->getIllumNum())
                    {
                        frameBuffer.at(curX).at(curY) = color + visible;
                    }
                    else
                        frameBuffer.at(curX).at(curY) = color + 1;
                }
            }
        }
//#pragma omp parallel for
        for (int curY = (y2 < 0) ? 0 : y2;
             curY <= ((y3 >= (int) bufHeight) ? (int) bufHeight - 1 : y3); curY++)
        {
            double aInc = 0;
            if (y2 != y3)
                aInc = (double) (curY - y2) / (y3 - y2);

            double bInc = 0;
            if (y1 != y3)
                bInc = (double) (curY - y1) / (y3 - y1);

            int xA = round(x2 + (x3 - x2) * aInc);
            int xB = round(x1 + (x3 - x1) * bInc);
            double zA = z2 + (z3 - z2) * aInc;
            double zB = z1 + (z3 - z1) * bInc;

            if (xA > xB)
            {
                std::swap(xA, xB);
                std::swap(zA, zB);
            }

            if (xA < 0)
                xA = 0;
            if (xB >= (int) bufWidth)
                xB = (int) bufWidth - 1;

            for (int curX = xA; curX <= xB; curX++)
            {
                double curZ = zA + (zB - zA) * (curX - xA) / (xB - xA);

                if (curZ >= depthBuffer.at(curX).at(curY))
                {
                    short visible = 0;
                    Eigen::MatrixXf newCoordinates(1, 4);
                    for (size_t i = 0; i < scene->getIllumNum() && !visible; i++)
                    {
                        newCoordinates << curX, curY, curZ, 1;

                        newCoordinates *= illumDotMatrices.at(i);
                        std::vector<std::vector<double>> *shadowMap =
                            &scene->getIlluminant(i).getShadowMap();
                        int x = round(newCoordinates(0, 0));
                        int y = round(newCoordinates(0, 1));

                        if (x < (int) shadowMap->size() && x >= 0 &&
                            y < (int) shadowMap->at(0).size() && y >= 0 &&
                            std::fabs(shadowMap->at(x).at(y) - newCoordinates(0, 2)) < 2)
                            visible = 1;
                    }
                    depthBuffer.at(curX).at(curY) = curZ;
                    if (scene->getIllumNum())
                    {
                        frameBuffer.at(curX).at(curY) = color + visible;
                    }
                    else
                        frameBuffer.at(curX).at(curY) = color + 1;
                }
            }
        }
        DDABordersForPolygon(x1, y1, z1, x2, y2, z2);
        DDABordersForPolygon(x1, y1, z1, x3, y3, z3);
        DDABordersForPolygon(x2, y2, z2, x3, y3, z3);
    }
}

void Drawer::zBufferAlg(CellScene *scene, size_t bufHeight, size_t bufWidth)
{
    depthBuffer.erase(depthBuffer.begin(), depthBuffer.end());
    frameBuffer.erase(frameBuffer.begin(), frameBuffer.end());

    for (size_t i = 0; i < bufWidth; i++)
    {
        depthBuffer.push_back(std::vector<double>(bufHeight, 0));
        frameBuffer.push_back(std::vector<size_t>(bufHeight, 0));
    }

    PolModel model;
    std::vector<Facet> facets;
    std::vector<Vertex> vertices;
    PolModel::model_t typeModel;

    for (size_t i = 0; i < scene->getModelsNum(); i++)
    {
        model = scene->getModel(i);
        facets = model.getFacets();
        vertices = model.getVertices();
        for (size_t j = 0; j < scene->getIllumNum(); j++)
            shadowMapForModel(facets, vertices, scene->getTransMatrix(),
                &scene->getIlluminant(j), bufWidth, bufHeight);
    }

    model = scene->getPlateModel();
    facets = model.getFacets();
    vertices = model.getVertices();
    for (size_t j = 0; j < scene->getIllumNum(); j++)
        shadowMapForModel(facets, vertices, scene->getTransMatrix(),
            &scene->getIlluminant(j), bufWidth, bufHeight);

    for (size_t i = 0; i < scene->getModelsNum(); i++)
    {
        model = scene->getModel(i);
        facets = model.getFacets();
        vertices = model.getVertices();
        typeModel = model.getModelType();
        zBufForModel(
            facets, vertices, scene->getTransMatrix(), 4 + typeModel * 2, scene, bufWidth, bufHeight);
    }
    model = scene->getPlateModel();
    facets = model.getFacets();
    vertices = model.getVertices();
    zBufForModel(
        facets, vertices, scene->getTransMatrix(), 1, scene, bufWidth, bufHeight);

    for (size_t i = 0; i < scene->getIllumNum(); i++)
        scene->getIlluminant(i).clearShadowMap();
}

QGraphicsScene *Drawer::drawScene(CellScene *scene, QRectF rect)
{
    size_t width = scene->getWidth() * SCALE_FACTOR;
    size_t height = scene->getHeight() * SCALE_FACTOR;
    qDebug() << "Сцена" << scene->getWidth() << " x " << scene->getHeight();

    scene->buildPlateModel(Dot3D(PLATE_START), Dot3D(width, height, PLATE_Z));

    using namespace std::chrono;
    nanoseconds start = duration_cast<nanoseconds>(system_clock::now().time_since_epoch());
    zBufferAlg(scene, rect.size().height(), rect.size().width());
    nanoseconds end = duration_cast<nanoseconds>(system_clock::now().time_since_epoch());

    qDebug() << "Время выполнения z-буфера" << size_t((end - start).count() / 1000000);




    QGraphicsScene *outScene = new QGraphicsScene;
    outScene->setSceneRect(rect);

    QImage *image =
        new QImage(rect.size().width(), rect.size().height(), QImage::Format_RGB32);
    image->fill(Qt::white);

    uint plateCol             = qRgb(GRASS_COLOR);
    uint darkPlateCol         = qRgb(DARK_GRASS_COLOR);
    uint blackCol             = qRgb(BLACK_COLOUR);

    uint boardCol             = qRgb(HOUS_COLOR);
    uint darkBoardCol         = qRgb(DARK_HOUS_COLOR);

    uint roofBoardCol         = qRgb(ROOF_HOUS_COLOR);
    uint darkRoofBoardCol     = qRgb(DARK_ROOF_HOUS_COLOR);

    uint windowsBoardCol      = qRgb(WINDOWS_HOUS_COLOR);
    uint darkWindowsBoardCol  = qRgb(DARK_WINDOWS_HOUS_COLOR);

    uint tableFoliageCol       = qRgb(TREE_TRUNK_COLOR);
    uint darkTableFoliageCol   = qRgb(DARK_TREE_TRUNK_COLOR);

    uint tableTrunkCol         = qRgb(TREE_TRUNK_COLOR);
    uint darkTableTrunkCol     = qRgb(DARK_TREE_TRUNK_COLOR);

    uint chairFoliageCol       = qRgb(TREE_TRUNK_COLOR);
    uint darkChairFoliageCol   = qRgb(DARK_TREE_TRUNK_COLOR);

    uint chairTrunkCol         = qRgb(TREE_TRUNK_COLOR);
    uint darkChairTrunkCol     = qRgb(DARK_TREE_TRUNK_COLOR);

    uint bedFoliageCol       = qRgb(TREE_TRUNK_COLOR);
    uint darkBedFoliageCol   = qRgb(DARK_TREE_TRUNK_COLOR);

    uint bedTrunkCol         = qRgb(TREE_TRUNK_COLOR);
    uint darkBedTrunkCol     = qRgb(DARK_TREE_TRUNK_COLOR);

    uint torsherFoliageCol       = qRgb(TREE_TRUNK_COLOR);
    uint darkTorsherFoliageCol   = qRgb(DARK_TREE_TRUNK_COLOR);

    uint torsherCol         = qRgb(TREE_TRUNK_COLOR);
    uint darkTorsherCol     = qRgb(DARK_TREE_TRUNK_COLOR);

    uint bedMatrasCol         = qRgb(MATRAS_COLOR);
    uint darkBedMatrasCol     = qRgb(MATRAS_DARK_COLOR);

    uint roadAsphaltCol       = qRgb(ROAD_ASPHALT_COLOR);
    uint darkRoadAsphaltCol   = qRgb(DARK_ROAD_ASPHALT_COLOR);

    uint roadStripeCol        = qRgb(ROAD_STRIPE_COLOR);
    uint darkRoadStripeCol    = qRgb(DARK_ROAD_STRIPE_COLOR);

    uint carCol               = qRgb(CAR_COLOR);
    uint darkCarCol           = qRgb(DARK_CAR_COLOR);

    uint wheelsCarCol         = qRgb(CAR_WHEELS_COLOR);
    uint darkWheelsCarCol     = qRgb(DARK_CAR_WHEELS_COLOR);

    uint glassCarCol          = qRgb(CAR_GLASS_COLOR);
    uint darkGlassCarCol      = qRgb(DARK_CAR_GLASS_COLOR);

    nanoseconds start2 = duration_cast<nanoseconds>(system_clock::now().time_since_epoch());

    for (size_t i = 0; i < rect.size().width() - 1; i++)
        for (size_t j = 0; j < rect.size().height() - 1; j++)
        {
            if (frameBuffer.at(i).at(j) == 1)
            {
                image->setPixel(i, j, darkPlateCol);
            }
            else if (frameBuffer.at(i).at(j) == 2)
            {
                image->setPixel(i, j, plateCol);
            }
            else if (frameBuffer.at(i).at(j) == 3)
            {
                image->setPixel(i, j, blackCol);
            }
            else if (frameBuffer.at(i).at(j) == 4)
            {
                image->setPixel(i, j, darkBoardCol);
            }
            else if (frameBuffer.at(i).at(j) == 5)
            {
                image->setPixel(i, j, boardCol);
            }
            else if (frameBuffer.at(i).at(j) == 6)
            {
                image->setPixel(i, j, darkRoofBoardCol);
            }
            else if (frameBuffer.at(i).at(j) == 7)
            {
                image->setPixel(i, j, roofBoardCol);
            }
            else if (frameBuffer.at(i).at(j) == 8)
            {
                image->setPixel(i, j, darkWindowsBoardCol);
            }
            else if (frameBuffer.at(i).at(j) == 9)
            {
                image->setPixel(i, j, windowsBoardCol);
            }
            else if (frameBuffer.at(i).at(j) == 10)
            {
                image->setPixel(i, j, darkTableFoliageCol);
            }
            else if (frameBuffer.at(i).at(j) == 11)
            {
                image->setPixel(i, j, tableFoliageCol);
            }
            else if (frameBuffer.at(i).at(j) == 12)
            {
                image->setPixel(i, j, darkTableTrunkCol);
            }
            else if (frameBuffer.at(i).at(j) == 13)
            {
                image->setPixel(i, j, tableTrunkCol);
            }
            else if (frameBuffer.at(i).at(j) == 14)
            {
                image->setPixel(i, j, darkChairFoliageCol);
            }
            else if (frameBuffer.at(i).at(j) == 15)
            {
                image->setPixel(i, j, chairFoliageCol);
            }
            else if (frameBuffer.at(i).at(j) == 16)
            {
                image->setPixel(i, j, darkChairTrunkCol);
            }
            else if (frameBuffer.at(i).at(j) == 17)
            {
                image->setPixel(i, j, chairTrunkCol);
            }
            else if (frameBuffer.at(i).at(j) == 18)
            {
                image->setPixel(i, j, bedFoliageCol);
            }
            else if (frameBuffer.at(i).at(j) == 19)
            {
                image->setPixel(i, j, darkBedFoliageCol);
            }
            else if (frameBuffer.at(i).at(j) == 20)
            {
                image->setPixel(i, j, bedTrunkCol);
            }
            else if (frameBuffer.at(i).at(j) == 21)
            {
                image->setPixel(i, j, darkBedTrunkCol);
            }
            else if (frameBuffer.at(i).at(j) == 22)
            {
                image->setPixel(i, j, darkTorsherCol);
            }
            else if (frameBuffer.at(i).at(j) == 23)
            {
                image->setPixel(i, j, torsherCol);
            }
//            else if (frameBuffer.at(i).at(j) == 24)
//            {
//                image->setPixel(i, j, torsherTrunkCol);
//            }
//            else if (frameBuffer.at(i).at(j) == 25)
//            {
//                image->setPixel(i, j, darkTorsherTrunkCol);
//            }
        }

    nanoseconds end2 = duration_cast<nanoseconds>(system_clock::now().time_since_epoch());
    qDebug() << "Время отрисовки" << size_t((end2 - start2).count() / 1000000);
    qDebug() << "Общее время"     << size_t((end2 - start2).count() / 1000000) +
                                     size_t((end - start).count()   / 1000000);


    outScene->addPixmap(QPixmap::fromImage(*image));
    delete image;
    for (size_t i = 0; i < scene->getIllumNum(); i++)
        scene->getIlluminant(i).clearShadowMap();

    return outScene;
}

int UsageFacade::addBoard(int xCell, int yCell, int modelLength, int modelHeight, int countFloors, int direction)
{
    xCell -= 1;
    yCell -= 1;

    if (xCell + modelLength - 1 >= (int) scene->getWidth() || \
        yCell + modelHeight - 1 >= (int) scene->getHeight())
    return 2;

    for (int i = yCell; i < yCell + modelHeight; i++)
    {
        for (int j = xCell; j < xCell + modelLength; j++)
        {
            if (scene->getUsedCells()[i][j] == 1)
            {
                qDebug() << "i = " << i << "j = " << j << "ячейка занята (шкаф)";
                return 1;
            }
        }
    }

    int xFactor;
    int yFactor;
    int zFactor;
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    if (direction == 2)
    {
        xFactor = xCell * SCALE_FACTOR + 10;
        yFactor = yCell * SCALE_FACTOR + 10;
        zFactor = PLATE_Z;
        //задняя
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR);
        //правая
        addQuad(vertices, facets,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor + countFloors * SCALE_FACTOR);
        //левая
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR);

        //передняя левая
        addQuad(vertices, facets,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR/2 - 1, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR/2 - 1, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR);
        //передняя правая
        addQuad(vertices, facets,
                xFactor + modelLength * SCALE_FACTOR,                yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR/2 + 1, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR/2 + 1, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                xFactor + modelLength * SCALE_FACTOR,                yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR);

        //низ шкафа
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor + modelLength * SCALE_FACTOR,         yFactor,                                  zFactor,
                    xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                    xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor);
        //крыша шкафа
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor + countFloors * SCALE_FACTOR,
                    xFactor + modelLength * SCALE_FACTOR,         yFactor,                                  zFactor + countFloors * SCALE_FACTOR,
                    xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                    xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR);
    }
    else if (direction == 1)
    {
        xFactor = xCell * SCALE_FACTOR + 10;
        yFactor = yCell * SCALE_FACTOR + 10;
        zFactor = PLATE_Z;
        //передняя
        addQuad(vertices, facets,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR);
        //правая
        addQuad(vertices, facets,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor + countFloors * SCALE_FACTOR);
        //левая
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR);

        //задняя левая
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR/2 - 1, yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR/2 - 1, yFactor, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR);
        //заддняя правая
        addQuad(vertices, facets,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR/2 + 1, yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR/2 + 1, yFactor, zFactor + countFloors * SCALE_FACTOR,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor + countFloors * SCALE_FACTOR);

        //низ шкафа
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor + modelLength * SCALE_FACTOR,         yFactor,                                  zFactor,
                    xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                    xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor);
        //крыша шкафа
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor + countFloors * SCALE_FACTOR,
                    xFactor + modelLength * SCALE_FACTOR,         yFactor,                                  zFactor + countFloors * SCALE_FACTOR,
                    xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                    xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR);
    }
    else if (direction == 3)//дверцы справа
    {
        xFactor = xCell * SCALE_FACTOR + 10;
        yFactor = yCell * SCALE_FACTOR + 10;
        zFactor = PLATE_Z;
        //задняя
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR);
        //правая правая
        addQuad(vertices, facets,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR/2 - 1, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR/2 - 1, zFactor + countFloors * SCALE_FACTOR,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor + countFloors * SCALE_FACTOR);
        //правая левая
        addQuad(vertices, facets,
                xFactor + modelLength * SCALE_FACTOR,                yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR/2 + 1, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR/2 + 1, zFactor + countFloors * SCALE_FACTOR,
                xFactor + modelLength * SCALE_FACTOR,                yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR);
        //левая
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR);
        //передняя
        addQuad(vertices, facets,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR);

        //низ шкафа
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor + modelHeight * SCALE_FACTOR,         yFactor,                                  zFactor,
                    xFactor + modelHeight * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                    xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor);
        //крыша шкафа
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor + countFloors * SCALE_FACTOR,
                    xFactor + modelLength * SCALE_FACTOR,         yFactor,                                  zFactor + countFloors * SCALE_FACTOR,
                    xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                    xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR);
    }
    else if (direction == 4)//дверцы слева
    {
        xFactor = xCell * SCALE_FACTOR + 10;
        yFactor = yCell * SCALE_FACTOR + 10;
        zFactor = PLATE_Z;
        //задняя
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR);
        //правая
        addQuad(vertices, facets,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor + countFloors * SCALE_FACTOR);
        //передняя
        addQuad(vertices, facets,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR);
        //левая левая
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR/2 - 1, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR/2 - 1, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR);
        //левая правая
        addQuad(vertices, facets,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR/2 + 1, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR/2 + 1, zFactor + countFloors * SCALE_FACTOR,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR);

        //низ шкафа
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor + modelLength * SCALE_FACTOR,         yFactor,                                  zFactor,
                    xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                    xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor);
        //крыша шкафа
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor + countFloors * SCALE_FACTOR,
                    xFactor + modelLength * SCALE_FACTOR,         yFactor,                                  zFactor + countFloors * SCALE_FACTOR,
                    xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR,
                    xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR);
    }

//    //стены шкафа
//    for (int i = 0; i < countFloors; i++)
//    {
//        for (int k = 0; k < 2; k++)
//        {
//            for (int j = 0; j < modelLength; j++)
//            {
//                addQuad(vertices, facets,
//                        xFactor,                yFactor, zFactor,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor,                yFactor, zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor,                yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor,                yFactor, zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor,                    yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor,                    yFactor, zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR,         yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR,         yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR);

//                xFactor += SCALE_FACTOR;
//            }

//            xFactor = xCell * SCALE_FACTOR + 10;
//            yFactor += SCALE_FACTOR * modelHeight;
//        }

//        yFactor = yCell * SCALE_FACTOR + 10;


//        for (int k = 0; k < 2; k++)
//        {
//            for (int j = 0; j < modelHeight; j++)
//            {
//                addQuad(vertices, facets,
//                       xFactor, yFactor,                zFactor,
//                       xFactor, yFactor + SCALE_FACTOR, zFactor,
//                       xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                       xFactor, yFactor,                zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor, yFactor,                zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                        xFactor, yFactor,                zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor, yFactor,                    zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                        xFactor, yFactor,                    zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR,         zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR,         zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR);

//                yFactor += SCALE_FACTOR;
//            }

//            yFactor = yCell * SCALE_FACTOR + 10;
//            xFactor += SCALE_FACTOR * modelLength;
//        }

//        xFactor = xCell * SCALE_FACTOR + 10;

//        zFactor += SCALE_FACTOR;
//    }

//    addQuad(vertices, facets,
//            xFactor,         yFactor,     zFactor,
//            xFactor + 2 * SCALE_FACTOR,         yFactor,                                  zFactor,
//            xFactor + 2 * SCALE_FACTOR, yFactor + 1 * SCALE_FACTOR, zFactor,
//            xFactor, yFactor + 1 * SCALE_FACTOR, zFactor);
    PolModel boardModel(vertices, facets, "Шкаф");
    boardModel.setUsedCell(xCell, yCell);
    boardModel.setHeightModel(modelHeight);
    boardModel.setWidthModel(modelLength);
    boardModel.setBoardHeight(countFloors);
    boardModel.setDirectionModel(direction);
    boardModel.setModelType(PolModel::Board);
    boardModel.setModelNum(scene->getModelsNum());
    scene->addModel(boardModel);

    return 0;
}

int UsageFacade::addBed(int xCell, int yCell, int direction)
{
    xCell -= 1;
    yCell -= 1;
    if (direction == 1 || direction == 2)
    {
        if (xCell + 2 - 1 >= (int) scene->getWidth() || \
            yCell + 3 - 1 >= (int) scene->getHeight())
        return 2;

        for (int i = yCell; i < yCell + 3; i++)
        {
            for (int j = xCell; j < xCell + 2; j++)
            {
                if (scene->getUsedCells()[i][j] == 1)
                {
                    qDebug() << "i = " << i << "j = " << j << "ячейка занята (кровать)";
                    return 1;
                }
            }
        }
    }
    else if (direction == 3 || direction == 4)
    {
        if (xCell + 3 - 1 >= (int) scene->getWidth() || \
            yCell + 2 - 1 >= (int) scene->getHeight())
        return 2;

        for (int i = yCell; i < yCell + 2; i++)
        {
            for (int j = xCell; j < xCell + 3; j++)
            {
                if (scene->getUsedCells()[i][j] == 1)
                {
                    qDebug() << "i = " << i << "j = " << j << "ячейка занята (кровать)";
                    return 1;
                }
            }
        }
    }

    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    int xFactor = xCell * SCALE_FACTOR + 10;
    int yFactor = yCell * SCALE_FACTOR + 10;
    int zFactor = PLATE_Z + SCALE_FACTOR/2;
    if (direction == 1)
    {
        //стены кровати
        for (int i = 0; i < 1; i++)
        {
            for (int k = 0; k < 2; k++)
            {
                for (int j = 0; j < 2; j++)
                {
                    addQuad(vertices, facets,
                            xFactor,                yFactor, zFactor,
                            xFactor + SCALE_FACTOR, yFactor, zFactor,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor,                yFactor, zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor,                yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor,                yFactor, zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor,                    yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor,                    yFactor, zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR,         yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR,         yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2);

                    xFactor += SCALE_FACTOR;
                }

                xFactor = xCell * SCALE_FACTOR + 10;
                yFactor += SCALE_FACTOR * 3;
            }

            yFactor = yCell * SCALE_FACTOR + 10;


            for (int k = 0; k < 2; k++)
            {
                for (int j = 0; j < 3; j++)
                {
                    addQuad(vertices, facets,
                           xFactor, yFactor,                zFactor,
                           xFactor, yFactor + SCALE_FACTOR, zFactor,
                           xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                           xFactor, yFactor,                zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor, yFactor,                zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor,                zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor, yFactor,                    zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor,                    zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR,         zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR,         zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2);

                    yFactor += SCALE_FACTOR;
                }

                yFactor = yCell * SCALE_FACTOR + 10;
                xFactor += SCALE_FACTOR * 2;
            }

            xFactor = xCell * SCALE_FACTOR + 10;

            zFactor += SCALE_FACTOR/2;
        }

        //верх кровати
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor + 2 * SCALE_FACTOR,         yFactor,                                  zFactor,
                    xFactor + 2 * SCALE_FACTOR, yFactor + 3 * SCALE_FACTOR, zFactor,
                    xFactor, yFactor + 3 * SCALE_FACTOR, zFactor);

        //спинка
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor + 2 * SCALE_FACTOR,         yFactor,                                  zFactor,
                    xFactor + 2 * SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
                    xFactor, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor,         yFactor + 10,                                  zFactor,
                    xFactor, yFactor + 10, zFactor + SCALE_FACTOR,
                    xFactor, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor,         yFactor + 10,     zFactor,
                    xFactor + 2 * SCALE_FACTOR,         yFactor + 10,                                  zFactor,
                    xFactor + 2 * SCALE_FACTOR, yFactor + 10, zFactor + SCALE_FACTOR,
                    xFactor, yFactor + 10, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor + 2 * SCALE_FACTOR,         yFactor,     zFactor,
                    xFactor + 2 * SCALE_FACTOR,         yFactor + 10,                                  zFactor,
                    xFactor + 2 * SCALE_FACTOR, yFactor + 10, zFactor + SCALE_FACTOR,
                    xFactor + 2 * SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor + SCALE_FACTOR,
                    xFactor + 2 * SCALE_FACTOR,         yFactor,                                  zFactor + SCALE_FACTOR,
                    xFactor + 2 * SCALE_FACTOR, yFactor + 10, zFactor + SCALE_FACTOR,
                    xFactor, yFactor + 10, zFactor + SCALE_FACTOR);


        //низ кровати//
        zFactor = PLATE_Z + SCALE_FACTOR/2;
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 2 * SCALE_FACTOR,         yFactor,                                  zFactor,
                xFactor + 2 * SCALE_FACTOR, yFactor + 3 * SCALE_FACTOR, zFactor,
                xFactor, yFactor + 3 * SCALE_FACTOR, zFactor);

        zFactor = PLATE_Z;
        //ножки кровати(л.п.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor,
                xFactor, yFactor + 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor + 10,                                  zFactor,
                xFactor, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor + 10,         yFactor,     zFactor,
                xFactor + 10,         yFactor + 10,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor + 10,     zFactor,
                xFactor + 10,         yFactor + 10,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10 + 2 * SCALE_FACTOR;
        //ножки кровати(п.п.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor,
                xFactor, yFactor + 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor + 10,                                  zFactor,
                xFactor, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor - 10,         yFactor,     zFactor,
                xFactor - 10,         yFactor + 10,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor + 10,     zFactor,
                xFactor - 10,         yFactor + 10,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10;
        yFactor = yCell * SCALE_FACTOR + 10 + 3 *SCALE_FACTOR;
        //ножки кровати(л.з.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor,
                xFactor, yFactor - 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor - 10,                                  zFactor,
                xFactor, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor + 10,         yFactor,     zFactor,
                xFactor + 10,         yFactor - 10,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor - 10,     zFactor,
                xFactor + 10,         yFactor - 10,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10 + 2 * SCALE_FACTOR;
        yFactor = yCell * SCALE_FACTOR + 10 + 3 *SCALE_FACTOR;
        //ножки кровати(п.з.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor,
                xFactor, yFactor - 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor - 10,                                  zFactor,
                xFactor, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor - 10,         yFactor,     zFactor,
                xFactor - 10,         yFactor - 10,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor - 10,     zFactor,
                xFactor - 10,         yFactor - 10,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
    }
    else if (direction == 2)//спинкой на наблюдателя
    {
        //стены кровати
        for (int i = 0; i < 1; i++)
        {
            for (int k = 0; k < 2; k++)
            {
                for (int j = 0; j < 2; j++)
                {
                    addQuad(vertices, facets,
                            xFactor,                yFactor, zFactor,
                            xFactor + SCALE_FACTOR, yFactor, zFactor,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor,                yFactor, zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor,                yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor,                yFactor, zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor,                    yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor,                    yFactor, zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR,         yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR,         yFactor, zFactor + SCALE_FACTOR/2,
                            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2);

                    xFactor += SCALE_FACTOR;
                }

                xFactor = xCell * SCALE_FACTOR + 10;
                yFactor += SCALE_FACTOR * 3;
            }

            yFactor = yCell * SCALE_FACTOR + 10;


            for (int k = 0; k < 2; k++)
            {
                for (int j = 0; j < 3; j++)
                {
                    addQuad(vertices, facets,
                           xFactor, yFactor,                zFactor,
                           xFactor, yFactor + SCALE_FACTOR, zFactor,
                           xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                           xFactor, yFactor,                zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor, yFactor,                zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor,                zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor, yFactor,                    zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor,                    zFactor + SCALE_FACTOR/2);
                    addQuad(vertices, facets,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR,         zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR,         zFactor + SCALE_FACTOR/2,
                            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/2);

                    yFactor += SCALE_FACTOR;
                }

                yFactor = yCell * SCALE_FACTOR + 10;
                xFactor += SCALE_FACTOR * 2;
            }

            xFactor = xCell * SCALE_FACTOR + 10;

            zFactor += SCALE_FACTOR/2;
        }

        //верх кровати
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor + 2 * SCALE_FACTOR,         yFactor,                                  zFactor,
                    xFactor + 2 * SCALE_FACTOR, yFactor + 3 * SCALE_FACTOR, zFactor,
                    xFactor, yFactor + 3 * SCALE_FACTOR, zFactor);

        yFactor = yFactor + 3 * SCALE_FACTOR;
        //спинка
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor + 2 * SCALE_FACTOR,         yFactor,                                  zFactor,
                    xFactor + 2 * SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
                    xFactor, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor,         yFactor - 10,                                  zFactor,
                    xFactor, yFactor - 10, zFactor + SCALE_FACTOR,
                    xFactor, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor,         yFactor - 10,     zFactor,
                    xFactor + 2 * SCALE_FACTOR,         yFactor - 10,                                  zFactor,
                    xFactor + 2 * SCALE_FACTOR, yFactor - 10, zFactor + SCALE_FACTOR,
                    xFactor, yFactor - 10, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor + 2 * SCALE_FACTOR,         yFactor,     zFactor,
                    xFactor + 2 * SCALE_FACTOR,         yFactor - 10,                                  zFactor,
                    xFactor + 2 * SCALE_FACTOR, yFactor - 10, zFactor + SCALE_FACTOR,
                    xFactor + 2 * SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor + SCALE_FACTOR,
                    xFactor + 2 * SCALE_FACTOR,         yFactor,                                  zFactor + SCALE_FACTOR,
                    xFactor + 2 * SCALE_FACTOR, yFactor - 10, zFactor + SCALE_FACTOR,
                    xFactor, yFactor - 10, zFactor + SCALE_FACTOR);

        yFactor = yFactor - 3 * SCALE_FACTOR;
        //низ кровати//
        zFactor = PLATE_Z + SCALE_FACTOR/2;
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 2 * SCALE_FACTOR,         yFactor,                                  zFactor,
                xFactor + 2 * SCALE_FACTOR, yFactor + 3 * SCALE_FACTOR, zFactor,
                xFactor, yFactor + 3 * SCALE_FACTOR, zFactor);

        zFactor = PLATE_Z;
        //ножки кровати(л.п.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor,
                xFactor, yFactor + 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor + 10,                                  zFactor,
                xFactor, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor + 10,         yFactor,     zFactor,
                xFactor + 10,         yFactor + 10,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor + 10,     zFactor,
                xFactor + 10,         yFactor + 10,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10 + 2 * SCALE_FACTOR;
        //ножки кровати(п.п.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor,
                xFactor, yFactor + 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor + 10,                                  zFactor,
                xFactor, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor - 10,         yFactor,     zFactor,
                xFactor - 10,         yFactor + 10,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor + 10,     zFactor,
                xFactor - 10,         yFactor + 10,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10;
        yFactor = yCell * SCALE_FACTOR + 10 + 3 *SCALE_FACTOR;
        //ножки кровати(л.з.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor,
                xFactor, yFactor - 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor - 10,                                  zFactor,
                xFactor, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor + 10,         yFactor,     zFactor,
                xFactor + 10,         yFactor - 10,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor - 10,     zFactor,
                xFactor + 10,         yFactor - 10,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10 + 2 * SCALE_FACTOR;
        yFactor = yCell * SCALE_FACTOR + 10 + 3 *SCALE_FACTOR;
        //ножки кровати(п.з.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor,
                xFactor, yFactor - 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor - 10,                                  zFactor,
                xFactor, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor - 10,         yFactor,     zFactor,
                xFactor - 10,         yFactor - 10,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor - 10,     zFactor,
                xFactor - 10,         yFactor - 10,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
    }
    else if (direction == 3)//спинкой вправо
    {
        //стены кровати(задняя)
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor + 3 * SCALE_FACTOR,         yFactor,                                  zFactor,
                    xFactor + 3 * SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                    xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        //стены кровати(левая)
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                    xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        //стены кровати(правая)
        addQuad(vertices, facets,
                    xFactor + 3 * SCALE_FACTOR,         yFactor,     zFactor,
                    xFactor + 3 * SCALE_FACTOR,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor + 3 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                    xFactor + 3 * SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2);
        //стены кровати(передняя)
        addQuad(vertices, facets,
                    xFactor,         yFactor + 2 * SCALE_FACTOR,     zFactor,
                    xFactor + 3 * SCALE_FACTOR,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor + 3 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                    xFactor, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2);

        //верх кровати
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor + SCALE_FACTOR/2,
                    xFactor + 3 * SCALE_FACTOR,         yFactor,                                  zFactor + SCALE_FACTOR/2,
                    xFactor + 3 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                    xFactor, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2);

        zFactor = zFactor + SCALE_FACTOR/2;
        //спинка
        addQuad(vertices, facets,
                    xFactor + 3 * SCALE_FACTOR,         yFactor,     zFactor,
                    xFactor + 3 * SCALE_FACTOR,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor + 3 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR,
                    xFactor + 3 * SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor + 3 * SCALE_FACTOR,         yFactor,     zFactor,
                    xFactor + 3 * SCALE_FACTOR - 10,         yFactor,                                  zFactor,
                    xFactor + 3 * SCALE_FACTOR - 10, yFactor, zFactor + SCALE_FACTOR,
                    xFactor + 3 * SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor + 3 * SCALE_FACTOR - 10,         yFactor,     zFactor,
                    xFactor + 3 * SCALE_FACTOR - 10,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor + 3 * SCALE_FACTOR - 10, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR,
                    xFactor + 3 * SCALE_FACTOR - 10, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor + 3 * SCALE_FACTOR - 10,         yFactor + 2 * SCALE_FACTOR,     zFactor,
                    xFactor + 3 * SCALE_FACTOR,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor + 3 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR,
                    xFactor + 3 * SCALE_FACTOR - 10, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor + 3 * SCALE_FACTOR - 10,         yFactor,     zFactor + SCALE_FACTOR,
                    xFactor + 3 * SCALE_FACTOR - 10,         yFactor + 2 * SCALE_FACTOR,                                  zFactor + SCALE_FACTOR,
                    xFactor + 3 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR,
                    xFactor + 3 * SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR);


        //низ кровати//
        zFactor = PLATE_Z + SCALE_FACTOR/2;
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 3 * SCALE_FACTOR,         yFactor,                                  zFactor,
                xFactor + 3 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor,
                xFactor, yFactor + 2 * SCALE_FACTOR, zFactor);

        zFactor = PLATE_Z;
        //ножки кровати(л.п.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor,
                xFactor, yFactor + 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor + 10,                                  zFactor,
                xFactor, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor + 10,         yFactor,     zFactor,
                xFactor + 10,         yFactor + 10,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor + 10,     zFactor,
                xFactor + 10,         yFactor + 10,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10 + 3 * SCALE_FACTOR;
        //ножки кровати(п.п.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor,
                xFactor, yFactor + 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor + 10,                                  zFactor,
                xFactor, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor - 10,         yFactor,     zFactor,
                xFactor - 10,         yFactor + 10,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor + 10,     zFactor,
                xFactor - 10,         yFactor + 10,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10;
        yFactor = yCell * SCALE_FACTOR + 10 + 2 *SCALE_FACTOR;
        //ножки кровати(л.з.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor,
                xFactor, yFactor - 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor - 10,                                  zFactor,
                xFactor, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor + 10,         yFactor,     zFactor,
                xFactor + 10,         yFactor - 10,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor - 10,     zFactor,
                xFactor + 10,         yFactor - 10,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10 + 3 * SCALE_FACTOR;
        yFactor = yCell * SCALE_FACTOR + 10 + 2 *SCALE_FACTOR;
        //ножки кровати(п.з.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor,
                xFactor, yFactor - 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor - 10,                                  zFactor,
                xFactor, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor - 10,         yFactor,     zFactor,
                xFactor - 10,         yFactor - 10,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor - 10,     zFactor,
                xFactor - 10,         yFactor - 10,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
    }
    else if (direction == 4)//спинкой влево
    {
        //стены кровати(задняя)
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor + 3 * SCALE_FACTOR,         yFactor,                                  zFactor,
                    xFactor + 3 * SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2,
                    xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        //стены кровати(левая)
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                    xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        //стены кровати(правая)
        addQuad(vertices, facets,
                    xFactor + 3 * SCALE_FACTOR,         yFactor,     zFactor,
                    xFactor + 3 * SCALE_FACTOR,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor + 3 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                    xFactor + 3 * SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/2);
        //стены кровати(передняя)
        addQuad(vertices, facets,
                    xFactor,         yFactor + 2 * SCALE_FACTOR,     zFactor,
                    xFactor + 3 * SCALE_FACTOR,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor + 3 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                    xFactor, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2);

        //верх кровати
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor + SCALE_FACTOR/2,
                    xFactor + 3 * SCALE_FACTOR,         yFactor,                                  zFactor + SCALE_FACTOR/2,
                    xFactor + 3 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2,
                    xFactor, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR/2);

        zFactor = zFactor + SCALE_FACTOR/2;
        //спинка
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR,
                    xFactor, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor,         yFactor,     zFactor,
                    xFactor + 10,         yFactor,                                  zFactor,
                    xFactor + 10, yFactor, zFactor + SCALE_FACTOR,
                    xFactor, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor + 10,         yFactor,     zFactor,
                    xFactor + 10,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor + 10, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR,
                    xFactor + 10, yFactor, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor + 10,         yFactor + 2 * SCALE_FACTOR,     zFactor,
                    xFactor,         yFactor + 2 * SCALE_FACTOR,                                  zFactor,
                    xFactor, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR,
                    xFactor + 10, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR);
        addQuad(vertices, facets,
                    xFactor + 10,         yFactor,     zFactor + SCALE_FACTOR,
                    xFactor + 10,         yFactor + 2 * SCALE_FACTOR,                                  zFactor + SCALE_FACTOR,
                    xFactor, yFactor + 2 * SCALE_FACTOR, zFactor + SCALE_FACTOR,
                    xFactor, yFactor, zFactor + SCALE_FACTOR);


        //низ кровати//
        zFactor = PLATE_Z + SCALE_FACTOR/2;
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 3 * SCALE_FACTOR,         yFactor,                                  zFactor,
                xFactor + 3 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor,
                xFactor, yFactor + 2 * SCALE_FACTOR, zFactor);

        zFactor = PLATE_Z;
        //ножки кровати(л.п.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor,
                xFactor, yFactor + 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor + 10,                                  zFactor,
                xFactor, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor + 10,         yFactor,     zFactor,
                xFactor + 10,         yFactor + 10,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor + 10,     zFactor,
                xFactor + 10,         yFactor + 10,                                  zFactor,
                xFactor + 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10 + 3 * SCALE_FACTOR;
        //ножки кровати(п.п.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor,
                xFactor, yFactor + 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor + 10,                                  zFactor,
                xFactor, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor - 10,         yFactor,     zFactor,
                xFactor - 10,         yFactor + 10,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor + 10,     zFactor,
                xFactor - 10,         yFactor + 10,                                  zFactor,
                xFactor - 10, yFactor + 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10;
        yFactor = yCell * SCALE_FACTOR + 10 + 2 *SCALE_FACTOR;
        //ножки кровати(л.з.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor,
                xFactor, yFactor - 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 10,         yFactor,                                  zFactor,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor - 10,                                  zFactor,
                xFactor, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor + 10,         yFactor,     zFactor,
                xFactor + 10,         yFactor - 10,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor + 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor - 10,     zFactor,
                xFactor + 10,         yFactor - 10,                                  zFactor,
                xFactor + 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10 + 3 * SCALE_FACTOR;
        yFactor = yCell * SCALE_FACTOR + 10 + 2 *SCALE_FACTOR;
        //ножки кровати(п.з.)
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor,
                xFactor, yFactor - 10, zFactor);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor - 10,         yFactor,                                  zFactor,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor,         yFactor - 10,                                  zFactor,
                xFactor, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor - 10,         yFactor,     zFactor,
                xFactor - 10,         yFactor - 10,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor - 10, yFactor, zFactor + SCALE_FACTOR/2);
        addQuad(vertices, facets,
                xFactor,         yFactor - 10,     zFactor,
                xFactor - 10,         yFactor - 10,                                  zFactor,
                xFactor - 10, yFactor - 10, zFactor + SCALE_FACTOR/2,
                xFactor, yFactor, zFactor + SCALE_FACTOR/2);
    }

    PolModel bedModel(vertices, facets, "Кровать");
    bedModel.setUsedCell(xCell, yCell);
    bedModel.setDirectionModel(direction);
    if (direction == 1 || direction == 2)
    {
        bedModel.setHeightModel(3);
        bedModel.setWidthModel(2);
        bedModel.setBoardHeight(1);
    }
    else if (direction == 3 || direction == 4)
    {
        bedModel.setHeightModel(2);
        bedModel.setWidthModel(3);
        bedModel.setBoardHeight(1);
    }
    bedModel.setModelType(PolModel::Bed);
    bedModel.setModelNum(scene->getModelsNum());
    scene->addModel(bedModel);

    return 0;
 }

int UsageFacade::addTable(int xCell, int yCell) //норм стол или стул
{
    xCell -= 1;
    yCell -= 1;

    if (xCell + 2 - 1 >= (int) scene->getWidth() || \
        yCell + 2 - 1 >= (int) scene->getHeight())
        return 2;

    for (int i = yCell; i < yCell + 2; i++)
    {
        for (int j = xCell; j < xCell + 2; j++)
        {
            if (scene->getUsedCells()[i][j] == 1)
            {
                qDebug() << "i = " << i << "j = " << j << "ячейка занята (стол)";
                return 1;
            }
        }
    }

    int xFactor = xCell * SCALE_FACTOR + 10;
    int yFactor = yCell * SCALE_FACTOR + 10;
    int zFactor = PLATE_Z + 5 * SCALE_FACTOR/3;

    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

//    //верх стола
//    addQuad(vertices, facets,
//                xFactor,                yFactor,                zFactor,
//                xFactor + 2 * SCALE_FACTOR, yFactor,                zFactor,
//                xFactor + 2 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor,
//                xFactor,                yFactor + 2 * SCALE_FACTOR, zFactor);

//    //низ стола
//    addQuad(vertices, facets,
//                xFactor,                yFactor,                zFactor - SCALE_FACTOR/3,
//                xFactor + 2 * SCALE_FACTOR, yFactor,                zFactor - SCALE_FACTOR/3,
//                xFactor + 2 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor - SCALE_FACTOR/3,
//                xFactor,                yFactor + 2 * SCALE_FACTOR, zFactor - SCALE_FACTOR/3);

//    //лево
//    addQuad(vertices, facets,
//                xFactor,                yFactor,                zFactor - SCALE_FACTOR/3,
//                xFactor, yFactor,                zFactor,
//                xFactor, yFactor + 2 * SCALE_FACTOR, zFactor,
//                xFactor,                yFactor + 2 * SCALE_FACTOR, zFactor - SCALE_FACTOR/3);

//    //право
//    addQuad(vertices, facets,
//                xFactor + 2 * SCALE_FACTOR,                yFactor,                zFactor - SCALE_FACTOR/3,
//                xFactor + 2 * SCALE_FACTOR, yFactor,                zFactor,
//                xFactor + 2 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor,
//                xFactor + 2 * SCALE_FACTOR,                yFactor + 2 * SCALE_FACTOR, zFactor - SCALE_FACTOR/3);

//    //зад
//    addQuad(vertices, facets,
//                xFactor,                yFactor,                zFactor - SCALE_FACTOR/3,
//                xFactor, yFactor,                zFactor,
//                xFactor + 2 * SCALE_FACTOR, yFactor, zFactor,
//                xFactor + 2 * SCALE_FACTOR,                yFactor, zFactor - SCALE_FACTOR/3);


//    //перед
//    addQuad(vertices, facets,
//                xFactor,                yFactor + 2 * SCALE_FACTOR,                zFactor - SCALE_FACTOR/3,
//                xFactor, yFactor + 2 * SCALE_FACTOR,                zFactor,
//                xFactor + 2 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor,
//                xFactor + 2 * SCALE_FACTOR,                yFactor + 2 * SCALE_FACTOR, zFactor - SCALE_FACTOR/3);
    //стены стола
    for (int i = 0; i < 1; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            for (int j = 0; j < 2; j++)
            {
                addQuad(vertices, facets,
                        xFactor,                yFactor, zFactor,
                        xFactor + SCALE_FACTOR, yFactor, zFactor,
                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/3,
                        xFactor,                yFactor, zFactor + SCALE_FACTOR/3);
                addQuad(vertices, facets,
                        xFactor,                yFactor, zFactor + SCALE_FACTOR/3,
                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/3,
                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/3,
                        xFactor,                yFactor, zFactor + SCALE_FACTOR/3);
                addQuad(vertices, facets,
                        xFactor,                    yFactor, zFactor + SCALE_FACTOR/3,
                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/3,
                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/3,
                        xFactor,                    yFactor, zFactor + SCALE_FACTOR/3);
                addQuad(vertices, facets,
                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/3,
                        xFactor + SCALE_FACTOR,         yFactor, zFactor + SCALE_FACTOR/3,
                        xFactor + SCALE_FACTOR,         yFactor, zFactor + SCALE_FACTOR/3,
                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR/3);

                xFactor += SCALE_FACTOR;
            }

            xFactor = xCell * SCALE_FACTOR + 10;
            yFactor += SCALE_FACTOR * 2;
        }

        yFactor = yCell * SCALE_FACTOR + 10;


        for (int k = 0; k < 2; k++)
        {
            for (int j = 0; j < 2; j++)
            {
                addQuad(vertices, facets,
                       xFactor, yFactor,                zFactor,
                       xFactor, yFactor + SCALE_FACTOR, zFactor,
                       xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/3,
                       xFactor, yFactor,                zFactor + SCALE_FACTOR/3);
                addQuad(vertices, facets,
                        xFactor, yFactor,                zFactor + SCALE_FACTOR/3,
                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/3,
                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/3,
                        xFactor, yFactor,                zFactor + SCALE_FACTOR/3);
                addQuad(vertices, facets,
                        xFactor, yFactor,                    zFactor + SCALE_FACTOR/3,
                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/3,
                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/3,
                        xFactor, yFactor,                    zFactor + SCALE_FACTOR/3);
                addQuad(vertices, facets,
                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/3,
                        xFactor, yFactor + SCALE_FACTOR,         zFactor + SCALE_FACTOR/3,
                        xFactor, yFactor + SCALE_FACTOR,         zFactor + SCALE_FACTOR/3,
                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR/3);

                yFactor += SCALE_FACTOR;
            }

            yFactor = yCell * SCALE_FACTOR + 10;
            xFactor += SCALE_FACTOR * 2;
        }

        xFactor = xCell * SCALE_FACTOR + 10;

        zFactor += SCALE_FACTOR/3;
    }
    //верх кровати
    addQuad(vertices, facets,
                xFactor,         yFactor,     zFactor,
                xFactor + 2 * SCALE_FACTOR,         yFactor,                                  zFactor,
                xFactor + 2 * SCALE_FACTOR, yFactor + 2 * SCALE_FACTOR, zFactor,
                xFactor, yFactor + 2 * SCALE_FACTOR, zFactor);

    zFactor = PLATE_Z;
    //ножки стола(л.п.)
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor + 10,         yFactor,                                  zFactor,
            xFactor + 10, yFactor + 10, zFactor,
            xFactor, yFactor + 10, zFactor);
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor + 10,         yFactor,                                  zFactor,
            xFactor + 10, yFactor, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor,         yFactor + 10,                                  zFactor,
            xFactor, yFactor + 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor + 10,         yFactor,     zFactor,
            xFactor + 10,         yFactor + 10,                                  zFactor,
            xFactor + 10, yFactor + 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor + 10, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor,         yFactor + 10,     zFactor,
            xFactor + 10,         yFactor + 10,                                  zFactor,
            xFactor + 10, yFactor + 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);

    xFactor = xCell * SCALE_FACTOR + 10 + 2 * SCALE_FACTOR;
    //ножки стола(п.п.)
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor - 10,         yFactor,                                  zFactor,
            xFactor - 10, yFactor + 10, zFactor,
            xFactor, yFactor + 10, zFactor);
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor - 10,         yFactor,                                  zFactor,
            xFactor - 10, yFactor, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor,         yFactor + 10,                                  zFactor,
            xFactor, yFactor + 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor - 10,         yFactor,     zFactor,
            xFactor - 10,         yFactor + 10,                                  zFactor,
            xFactor - 10, yFactor + 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor - 10, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor,         yFactor + 10,     zFactor,
            xFactor - 10,         yFactor + 10,                                  zFactor,
            xFactor - 10, yFactor + 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);

    xFactor = xCell * SCALE_FACTOR + 10;
    yFactor = yCell * SCALE_FACTOR + 10 + 2 *SCALE_FACTOR;
    //ножки кровати(л.з.)
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor + 10,         yFactor,                                  zFactor,
            xFactor + 10, yFactor - 10, zFactor,
            xFactor, yFactor - 10, zFactor);
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor + 10,         yFactor,                                  zFactor,
            xFactor + 10, yFactor, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor,         yFactor - 10,                                  zFactor,
            xFactor, yFactor - 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor + 10,         yFactor,     zFactor,
            xFactor + 10,         yFactor - 10,                                  zFactor,
            xFactor + 10, yFactor - 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor + 10, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor,         yFactor - 10,     zFactor,
            xFactor + 10,         yFactor - 10,                                  zFactor,
            xFactor + 10, yFactor - 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);

    xFactor = xCell * SCALE_FACTOR + 10 + 2 * SCALE_FACTOR;
    yFactor = yCell * SCALE_FACTOR + 10 + 2 *SCALE_FACTOR;
    //ножки стола(п.з.)
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor - 10,         yFactor,                                  zFactor,
            xFactor - 10, yFactor - 10, zFactor,
            xFactor, yFactor - 10, zFactor);
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor - 10,         yFactor,                                  zFactor,
            xFactor - 10, yFactor, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor,         yFactor,     zFactor,
            xFactor,         yFactor - 10,                                  zFactor,
            xFactor, yFactor - 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor - 10,         yFactor,     zFactor,
            xFactor - 10,         yFactor - 10,                                  zFactor,
            xFactor - 10, yFactor - 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor - 10, yFactor, zFactor + 5 * SCALE_FACTOR/3);
    addQuad(vertices, facets,
            xFactor,         yFactor - 10,     zFactor,
            xFactor - 10,         yFactor - 10,                                  zFactor,
            xFactor - 10, yFactor - 10, zFactor + 5 * SCALE_FACTOR/3,
            xFactor, yFactor, zFactor + 5 * SCALE_FACTOR/3);
//    addQuad(vertices, facets,
//            xFactor,                yFactor,                zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR, yFactor,                zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR + 100,
//            xFactor,                yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR + 100);

//    addQuad(vertices, facets,
//            xFactor,                yFactor, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR, yFactor, zFactor + 100 + SCALE_FACTOR * 7 / 6,
//            xFactor,                yFactor, zFactor + 100 + SCALE_FACTOR * 7 / 6);
//    addQuad(vertices, facets,
//            xFactor, yFactor,                zFactor + SCALE_FACTOR + 100,
//            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR + 100,
//            xFactor, yFactor + SCALE_FACTOR, zFactor + 100 + SCALE_FACTOR * 7 / 6,
//            xFactor, yFactor,                zFactor + 100 + SCALE_FACTOR * 7 / 6);
//    addQuad(vertices, facets,
//            xFactor + SCALE_FACTOR, yFactor,                zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + 100 + SCALE_FACTOR * 7 / 6,
//            xFactor + SCALE_FACTOR, yFactor,                zFactor + 100 + SCALE_FACTOR * 7 / 6);
//    addQuad(vertices, facets,
//            xFactor,                yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + 100 + SCALE_FACTOR * 7 / 6,
//            xFactor,                yFactor + SCALE_FACTOR, zFactor + 100 + SCALE_FACTOR * 7 / 6);

//    addQuad(vertices, facets,
//            xFactor,                yFactor,                zFactor + 100 + SCALE_FACTOR * 7 / 6,
//            xFactor + SCALE_FACTOR, yFactor,                zFactor + 100 + SCALE_FACTOR * 7 / 6,
//            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + 100 + SCALE_FACTOR * 7 / 6,
//            xFactor,                yFactor + SCALE_FACTOR, zFactor + 100 + SCALE_FACTOR * 7 / 6);

//    addQuad(vertices, facets,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR + 100);
//    addQuad(vertices, facets,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR + 100);
//    addQuad(vertices, facets,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR + 100);
//    addQuad(vertices, facets,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR + 100);
    PolModel TableTrunkModel(vertices, facets, "Стол");
    TableTrunkModel.setUsedCell(xCell, yCell);
    TableTrunkModel.setHeightModel(2);
    TableTrunkModel.setWidthModel(2);
    TableTrunkModel.setModelType(PolModel::tableTrunk);
    TableTrunkModel.setModelNum(scene->getModelsNum());
    scene->addModel(TableTrunkModel);


//    std::vector<Vertex> vertices;
//    std::vector<Facet> facets;


//    addQuad(vertices, facets,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR + 100);
//    addQuad(vertices, facets,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR + 100);
//    addQuad(vertices, facets,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR + 100);
//    addQuad(vertices, facets,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + SCALE_FACTOR * 3 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR + 100,
//            xFactor + SCALE_FACTOR * 2 / 5, yFactor + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR + 100);

//    PolModel TableTrunkModel(vertices, facets, "Ножка стола");
//    TableTrunkModel.setUsedCell(xCell, yCell);
//    TableTrunkModel.setHeightModel(1);
//    TableTrunkModel.setWidthModel(1);
//    TableTrunkModel.setModelType(PolModel::tableTrunk);
//    TableTrunkModel.setModelNum(scene->getModelsNum());
//    scene->addModel(TableTrunkModel);

    return 0;
}


int UsageFacade::addChair(int xCell, int yCell, int direction)//табуретка
{
    xCell -= 1;
    yCell -= 1;

    if (xCell >= (int) scene->getWidth() || yCell >= (int) scene->getHeight())
        return 2;

    if (scene->getUsedCells()[yCell][xCell] == 1)
    {
        qDebug() << "i = " << xCell << "j = " << xCell << "ячейка занята (стул)";
        return 1;
    }

    int xFactor = xCell * SCALE_FACTOR + 10;
    int yFactor = yCell * SCALE_FACTOR + 10;
    int zFactor = PLATE_Z;

    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    //сидушка
    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor + SCALE_FACTOR,
            xFactor + SCALE_FACTOR, yFactor,                zFactor + SCALE_FACTOR,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
            xFactor,                yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR);

    addQuad(vertices, facets,
            xFactor,                yFactor, zFactor + SCALE_FACTOR,
            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR * 3 / 2,
            xFactor,                yFactor, zFactor + SCALE_FACTOR * 3 / 2);
    addQuad(vertices, facets,
            xFactor, yFactor,                zFactor + SCALE_FACTOR,
            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
            xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR * 3 / 2,
            xFactor, yFactor,                zFactor + SCALE_FACTOR * 3 / 2);
    addQuad(vertices, facets,
            xFactor + SCALE_FACTOR, yFactor,                zFactor + SCALE_FACTOR,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR * 3 / 2,
            xFactor + SCALE_FACTOR, yFactor,                zFactor + SCALE_FACTOR * 3 / 2);
    addQuad(vertices, facets,
            xFactor,                yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR * 3 / 2,
            xFactor,                yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR * 3 / 2);

    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor + SCALE_FACTOR * 3 / 2,
            xFactor + SCALE_FACTOR, yFactor,                zFactor + SCALE_FACTOR * 3 / 2,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR * 3 / 2,
            xFactor,                yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR * 3 / 2);

    zFactor = zFactor + SCALE_FACTOR * 3/2;
    //задняя спинка зад
    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor,
            xFactor + SCALE_FACTOR, yFactor,                zFactor,
            xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
            xFactor,                yFactor, zFactor + SCALE_FACTOR);
    //задняя спинка право
    addQuad(vertices, facets,
            xFactor + SCALE_FACTOR,                yFactor,                zFactor,
            xFactor + SCALE_FACTOR, yFactor + 10,                zFactor,
            xFactor + SCALE_FACTOR, yFactor + 10, zFactor + SCALE_FACTOR,
            xFactor + SCALE_FACTOR,                yFactor, zFactor + SCALE_FACTOR);
    //задняя спинка лево
    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor,
            xFactor, yFactor + 10,                zFactor,
            xFactor, yFactor + 10, zFactor + SCALE_FACTOR,
            xFactor,                yFactor, zFactor + SCALE_FACTOR);
    //задняя спинка перед
    addQuad(vertices, facets,
            xFactor,                yFactor + 10,                zFactor,
            xFactor + SCALE_FACTOR, yFactor + 10,                zFactor,
            xFactor + SCALE_FACTOR, yFactor + 10, zFactor + SCALE_FACTOR,
            xFactor,                yFactor + 10, zFactor + SCALE_FACTOR);
    //задняя спинка верх
    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor + SCALE_FACTOR,
            xFactor + SCALE_FACTOR, yFactor,                zFactor + SCALE_FACTOR,
            xFactor + SCALE_FACTOR, yFactor + 10, zFactor + SCALE_FACTOR,
            xFactor,                yFactor + 10, zFactor + SCALE_FACTOR);

    yFactor = yFactor + 10;
    //левая спинка зад
    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor,
            xFactor + 5, yFactor,                zFactor,
            xFactor + 5, yFactor, zFactor + SCALE_FACTOR/4,
            xFactor,                yFactor, zFactor + SCALE_FACTOR/4);
    //левая спинка право
    addQuad(vertices, facets,
            xFactor + 5,                yFactor,                zFactor,
            xFactor + 5, yFactor + SCALE_FACTOR - 10,                zFactor,
            xFactor + 5, yFactor + SCALE_FACTOR - 10, zFactor + SCALE_FACTOR/4,
            xFactor + 5,                yFactor, zFactor + SCALE_FACTOR/4);
    //левая спинка лево
    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor,
            xFactor, yFactor + SCALE_FACTOR - 10,                zFactor,
            xFactor, yFactor + SCALE_FACTOR - 10, zFactor + SCALE_FACTOR/4,
            xFactor,                yFactor, zFactor + SCALE_FACTOR/4);
    //левая спинка перед
    addQuad(vertices, facets,
            xFactor,                yFactor + SCALE_FACTOR - 10,                zFactor,
            xFactor + 5, yFactor + SCALE_FACTOR - 10,                zFactor,
            xFactor + 5, yFactor, zFactor + SCALE_FACTOR/4,
            xFactor,                yFactor + SCALE_FACTOR - 10, zFactor + SCALE_FACTOR/4);
    //левая спинка верх
    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor + SCALE_FACTOR/4,
            xFactor + 5, yFactor,                zFactor + SCALE_FACTOR/4,
            xFactor + 5, yFactor + SCALE_FACTOR - 10, zFactor + SCALE_FACTOR/4,
            xFactor,                yFactor + SCALE_FACTOR - 10, zFactor + SCALE_FACTOR/4);

    xFactor = xFactor + SCALE_FACTOR - 5;
    //правая спинка зад
    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor,
            xFactor + 5, yFactor,                zFactor,
            xFactor + 5, yFactor, zFactor + SCALE_FACTOR/4,
            xFactor,                yFactor, zFactor + SCALE_FACTOR/4);
    //правая спинка право
    addQuad(vertices, facets,
            xFactor + 5,                yFactor,                zFactor,
            xFactor + 5, yFactor + SCALE_FACTOR - 10,                zFactor,
            xFactor + 5, yFactor + SCALE_FACTOR - 10, zFactor + SCALE_FACTOR/4,
            xFactor + 5,                yFactor, zFactor + SCALE_FACTOR/4);
    //правая спинка лево
    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor,
            xFactor, yFactor + SCALE_FACTOR - 10,                zFactor,
            xFactor, yFactor + SCALE_FACTOR - 10, zFactor + SCALE_FACTOR/4,
            xFactor,                yFactor, zFactor + SCALE_FACTOR/4);
    //правая спинка перед
    addQuad(vertices, facets,
            xFactor,                yFactor + SCALE_FACTOR - 10,                zFactor,
            xFactor + 5, yFactor + SCALE_FACTOR - 10,                zFactor,
            xFactor + 5, yFactor, zFactor + SCALE_FACTOR/4,
            xFactor,                yFactor + SCALE_FACTOR - 10, zFactor + SCALE_FACTOR/4);
    //правая спинка верх
    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor + SCALE_FACTOR/4,
            xFactor + 5, yFactor,                zFactor + SCALE_FACTOR/4,
            xFactor + 5, yFactor + SCALE_FACTOR - 10, zFactor + SCALE_FACTOR/4,
            xFactor,                yFactor + SCALE_FACTOR - 10, zFactor + SCALE_FACTOR/4);

    xFactor = xFactor - SCALE_FACTOR + 5;
    yFactor = yFactor - 10;
    zFactor = zFactor - SCALE_FACTOR * 3/2;
    //ножки
    addQuad(vertices, facets,
            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor - 20 + SCALE_FACTOR * 3 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor - 20 + SCALE_FACTOR * 3 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR,
            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor - 20+ SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor - 20+ SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor- 20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor -20 + SCALE_FACTOR * 2 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor -20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR);

    addQuad(vertices, facets,
            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor + 20 + SCALE_FACTOR * 3 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor + 20 + SCALE_FACTOR * 3 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR,
            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor + 20+ SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor + 20+ SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor +20 + SCALE_FACTOR * 2 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor +20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR);

    addQuad(vertices, facets,
            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor + 20 + SCALE_FACTOR * 3 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor + 20 + SCALE_FACTOR * 3 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR,
            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor + 20+ SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor + 20+ SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor +20 + SCALE_FACTOR * 2 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor +20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR);

    addQuad(vertices, facets,
            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor - 20 + SCALE_FACTOR * 3 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor - 20 + SCALE_FACTOR * 3 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR,
            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor - 20+ SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 2 / 5, zFactor,
            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor - 20+ SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
    addQuad(vertices, facets,
            xFactor -20 + SCALE_FACTOR * 2 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
            xFactor -20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR);

    PolModel ChairFoliageModel(vertices, facets, "Стул");
    ChairFoliageModel.setUsedCell(xCell, yCell);
    ChairFoliageModel.setHeightModel(1);
    ChairFoliageModel.setWidthModel(1);
    if (direction == 1)
    {
        ChairFoliageModel.rotateZ(180);
    }
    else if (direction == 3)
    {
        ChairFoliageModel.rotateZ(-90);
    }
    else if (direction == 4)
    {
        ChairFoliageModel.rotateZ(90);
    }
    ChairFoliageModel.setDirectionModel(direction);
    ChairFoliageModel.setModelType(PolModel::chairFoliage);
    ChairFoliageModel.setModelNum(scene->getModelsNum());
    scene->addModel(ChairFoliageModel);

//    std::vector<Vertex> vertices;
//    std::vector<Facet> facets;

//    addQuad(vertices, facets,
//            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor - 20 + SCALE_FACTOR * 3 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor - 20 + SCALE_FACTOR * 3 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR,
//            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor - 20+ SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor - 20+ SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor- 20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor -20 + SCALE_FACTOR * 2 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor -20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR);

//    addQuad(vertices, facets,
//            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + 20 + SCALE_FACTOR * 3 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + 20 + SCALE_FACTOR * 3 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR,
//            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor + 20+ SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + 20+ SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor +20 + SCALE_FACTOR * 2 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor -20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor +20 + SCALE_FACTOR * 2 / 5, yFactor - 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR);

//    addQuad(vertices, facets,
//            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + 20 + SCALE_FACTOR * 3 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + 20 + SCALE_FACTOR * 3 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR,
//            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor + 20+ SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor + 20+ SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor +20 + SCALE_FACTOR * 2 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor +20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor +20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR);

//    addQuad(vertices, facets,
//            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor - 20 + SCALE_FACTOR * 3 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor - 20 + SCALE_FACTOR * 3 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR,
//            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor - 20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor - 20+ SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 2 / 5, zFactor,
//            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor - 20+ SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 2 / 5, zFactor + SCALE_FACTOR);
//    addQuad(vertices, facets,
//            xFactor -20 + SCALE_FACTOR * 2 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor,
//            xFactor -20 + SCALE_FACTOR * 3 / 5, yFactor +20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR,
//            xFactor -20 + SCALE_FACTOR * 2 / 5, yFactor + 20 + SCALE_FACTOR * 3 / 5, zFactor + SCALE_FACTOR);

//    PolModel ChairTrunkModel(vertices, facets, "Ножки стула");
//    ChairTrunkModel.setUsedCell(xCell, yCell);
//    ChairTrunkModel.setHeightModel(1);
//    ChairTrunkModel.setWidthModel(1);
//    ChairTrunkModel.setModelType(PolModel::chairTrunk);
//    ChairTrunkModel.setModelNum(scene->getModelsNum());
//    scene->addModel(ChairTrunkModel);

    return 0;
}

int UsageFacade::addTorsher(int xCell, int yCell)//торшер
{
    xCell -= 1;
    yCell -= 1;

    if (xCell >= (int) scene->getWidth() || yCell >= (int) scene->getHeight())
        return 2;

    if (scene->getUsedCells()[yCell][xCell] == 1)
    {
        qDebug() << "i = " << xCell << "j = " << xCell << "ячейка занята (торшер)";
        return 1;
    }

    int xFactor = xCell * SCALE_FACTOR + 10;
    int yFactor = yCell * SCALE_FACTOR + 10;
    int zFactor = PLATE_Z;

    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    //нижняя подставка(зад)
    addQuad(vertices, facets,
            xFactor,                yFactor,                zFactor,
            xFactor + SCALE_FACTOR, yFactor,                zFactor,
            xFactor + SCALE_FACTOR, yFactor, zFactor + 10,
            xFactor,                yFactor, zFactor + 10);
    //нижняя подставка(лево)
    addQuad(vertices, facets,
            xFactor,                yFactor, zFactor,
            xFactor, yFactor + SCALE_FACTOR, zFactor,
            xFactor, yFactor + SCALE_FACTOR, zFactor + 10,
            xFactor,                yFactor, zFactor + 10);
    //нижняя подставка(перед)
    addQuad(vertices, facets,
            xFactor,                yFactor+SCALE_FACTOR, zFactor,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + 10,
            xFactor,                yFactor+SCALE_FACTOR, zFactor + 10);
    //нижняя подставка(право)
    addQuad(vertices, facets,
            xFactor + SCALE_FACTOR,                yFactor, zFactor,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + 10,
            xFactor + SCALE_FACTOR,                yFactor, zFactor + 10);
    //нижняя подставка(низ)
    addQuad(vertices, facets,
            xFactor,                yFactor, zFactor,
            xFactor + SCALE_FACTOR, yFactor, zFactor,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor,
            xFactor,                yFactor + SCALE_FACTOR, zFactor);
    //нижняя подставка(верх)
    addQuad(vertices, facets,
            xFactor,                yFactor, zFactor + 10,
            xFactor + SCALE_FACTOR, yFactor, zFactor + 10,
            xFactor + SCALE_FACTOR, yFactor + SCALE_FACTOR, zFactor + 10,
            xFactor,                yFactor + SCALE_FACTOR, zFactor + 10);

    xFactor = xCell * SCALE_FACTOR + 10 + SCALE_FACTOR/2 - 5;
    yFactor = yCell * SCALE_FACTOR + 10 + SCALE_FACTOR/2 - 5;
    zFactor = PLATE_Z + 10;
    //ножка зад
    addQuad(vertices, facets,
            xFactor,                yFactor, zFactor,
            xFactor + 10, yFactor, zFactor,
            xFactor + 10, yFactor, zFactor + 2.5 * SCALE_FACTOR,
            xFactor,                yFactor, zFactor + 2.5 * SCALE_FACTOR);
    //ножка лево
    addQuad(vertices, facets,
            xFactor,                yFactor, zFactor,
            xFactor, yFactor + 10, zFactor,
            xFactor, yFactor + 10, zFactor + 2.5 * SCALE_FACTOR,
            xFactor,                yFactor, zFactor + 2.5 * SCALE_FACTOR);
    //ножка перед
    addQuad(vertices, facets,
            xFactor,                yFactor + 10, zFactor,
            xFactor + 10, yFactor + 10, zFactor,
            xFactor + 10, yFactor + 10, zFactor + 2.5 * SCALE_FACTOR,
            xFactor,                yFactor + 10, zFactor + 2.5 * SCALE_FACTOR);
    //ножка право
    addQuad(vertices, facets,
            xFactor + 10,                yFactor, zFactor,
            xFactor + 10, yFactor + 10, zFactor,
            xFactor + 10, yFactor + 10, zFactor + 2.5 * SCALE_FACTOR,
            xFactor + 10,                yFactor, zFactor + 2.5 * SCALE_FACTOR);

    xFactor = xCell * SCALE_FACTOR + 10 + SCALE_FACTOR/2 - 10;
    yFactor = yCell * SCALE_FACTOR + 10 + SCALE_FACTOR/2 - 10;
    zFactor = zFactor + 2.5 * SCALE_FACTOR;

    //сама параша (левая)
    addQuad(vertices, facets,
            xFactor,                yFactor, zFactor + 20,
            xFactor - 20, yFactor - 20, zFactor - 20,
            xFactor - 20, yFactor + 40, zFactor - 20,
            xFactor,                yFactor + 20, zFactor + 20);

    //сама параша (задняя)
    addQuad(vertices, facets,
            xFactor,                yFactor, zFactor + 20,
            xFactor - 20,  yFactor - 20, zFactor - 20,
            xFactor + 40, yFactor - 20, zFactor - 20,
            xFactor + 20,                yFactor, zFactor + 20);

    //сама параша (правая)
    addQuad(vertices, facets,
            xFactor + 20,                yFactor, zFactor + 20,
            xFactor + 40,  yFactor - 20, zFactor - 20,
            xFactor + 40, yFactor + 40, zFactor - 20,
            xFactor + 20,                yFactor + 20, zFactor + 20);

    //сама параша (передняя)
    addQuad(vertices, facets,
            xFactor,                yFactor + 20, zFactor + 20,
            xFactor - 20,  yFactor + 40, zFactor - 20,
            xFactor + 40, yFactor + 40, zFactor - 20,
            xFactor + 20,                yFactor + 20, zFactor + 20);
    //крыша торшера
    addQuad(vertices, facets,
            xFactor,                yFactor, zFactor + 20,
            xFactor + 20,  yFactor, zFactor + 20,
            xFactor + 20, yFactor + 20, zFactor + 20,
            xFactor,                yFactor + 20, zFactor + 20);


    PolModel torsherModel(vertices, facets, "Торшер");
    torsherModel.setUsedCell(xCell, yCell);
    torsherModel.setHeightModel(1);
    torsherModel.setWidthModel(1);
    torsherModel.setModelType(PolModel::Torsher);
    torsherModel.setModelNum(scene->getModelsNum());
    scene->addModel(torsherModel);
}

int UsageFacade::addTv(int xCell, int yCell, int modelLength, int modelHeight, int countFloors, int direction)
{
    xCell -= 1;
    yCell -= 1;

    if (xCell + modelLength - 1 >= (int) scene->getWidth() || \
        yCell + modelHeight - 1 >= (int) scene->getHeight())
    return 2;

    for (int i = yCell; i < yCell + modelHeight; i++)
    {
        for (int j = xCell; j < xCell + modelLength; j++)
        {
            if (scene->getUsedCells()[i][j] == 1)
            {
                qDebug() << "i = " << i << "j = " << j << "ячейка занята (шкаф)";
                return 1;
            }
        }
    }

    int xFactor = xCell * SCALE_FACTOR + 10;
    int yFactor = yCell * SCALE_FACTOR + 10;
    int zFactor = PLATE_Z;
    std::vector<Vertex> vertices;
    std::vector<Facet> facets;

    if (direction == 1)
    {
        //нижняя подставка(зад)
        addQuad(vertices, facets,
                xFactor,                yFactor,                zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor,                zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor + 10,
                xFactor,                yFactor, zFactor + 10);
        //нижняя подставка(лево)
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor + 10,
                xFactor,                yFactor, zFactor + 10);
        //нижняя подставка(перед)
        addQuad(vertices, facets,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + 10,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor + 10);
        //нижняя подставка(право)
        addQuad(vertices, facets,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + 10,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor + 10);
        //нижняя подставка(низ)
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor);
        //нижняя подставка(верх)
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor + 10,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor + 10,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + 10,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor + 10);

        xFactor = xCell * SCALE_FACTOR + 10 + modelLength * SCALE_FACTOR/2 - 10;
        yFactor = yCell * SCALE_FACTOR + 10 + modelHeight * SCALE_FACTOR/2 - 10;
        zFactor = zFactor + 10;
        //ножка зад
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor + 20, yFactor, zFactor,
                xFactor + 20, yFactor, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);
        //ножка лево
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor, yFactor + 20, zFactor,
                xFactor, yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);
        //ножка перед
        addQuad(vertices, facets,
                xFactor,                yFactor + 20, zFactor,
                xFactor + 20, yFactor + 20, zFactor,
                xFactor + 20, yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2);
        //ножка право
        addQuad(vertices, facets,
                xFactor + 20,                yFactor, zFactor,
                xFactor + 20, yFactor + 20, zFactor,
                xFactor + 20, yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor + 20,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);

        xFactor = xCell * SCALE_FACTOR + 10;
        zFactor = PLATE_Z + 10 + countFloors * SCALE_FACTOR/2;
        //экран зад
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);
        //экран лево
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor, yFactor + 20, zFactor,
                xFactor, yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);
        //экран право
        addQuad(vertices, facets,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + 20, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);
        //экран перед
        addQuad(vertices, facets,
                xFactor,                yFactor + 20, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + 20, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2);
        //экран верх
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor + modelLength * SCALE_FACTOR, yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2);
        //экран низ
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + 20, zFactor,
                xFactor,                yFactor + 20, zFactor);
    }
    else if (direction == 2)
    {
        //нижняя подставка(зад)
        addQuad(vertices, facets,
                xFactor,                yFactor,                zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor,                zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor + 10,
                xFactor,                yFactor, zFactor + 10);
        //нижняя подставка(лево)
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor + 10,
                xFactor,                yFactor, zFactor + 10);
        //нижняя подставка(перед)
        addQuad(vertices, facets,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + 10,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor + 10);
        //нижняя подставка(право)
        addQuad(vertices, facets,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + 10,
                xFactor + modelLength * SCALE_FACTOR,                yFactor, zFactor + 10);
        //нижняя подставка(низ)
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor);
        //нижняя подставка(верх)
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor + 10,
                xFactor + modelLength * SCALE_FACTOR, yFactor, zFactor + 10,
                xFactor + modelLength * SCALE_FACTOR, yFactor + modelHeight * SCALE_FACTOR, zFactor + 10,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor + 10);

        xFactor = xCell * SCALE_FACTOR + 10 + modelLength * SCALE_FACTOR/2 - 10;
        yFactor = yCell * SCALE_FACTOR + 10 + modelHeight * SCALE_FACTOR/2 - 10;
        zFactor = zFactor + 10;
        //ножка зад
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor + 20, yFactor, zFactor,
                xFactor + 20, yFactor, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);
        //ножка лево
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor, yFactor + 20, zFactor,
                xFactor, yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);
        //ножка перед
        addQuad(vertices, facets,
                xFactor,                yFactor + 20, zFactor,
                xFactor + 20, yFactor + 20, zFactor,
                xFactor + 20, yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2);
        //ножка право
        addQuad(vertices, facets,
                xFactor + 20,                yFactor, zFactor,
                xFactor + 20, yFactor + 20, zFactor,
                xFactor + 20, yFactor + 20, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor + 20,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);

        yFactor = xCell * SCALE_FACTOR + 10;
        zFactor = PLATE_Z + 10 + countFloors * SCALE_FACTOR/2;
        //экран зад
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);
        //экран лево
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor + 20, yFactor, zFactor,
                xFactor + 20, yFactor, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);
        //экран право
        addQuad(vertices, facets,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + 20, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + 20, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor,                yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR/2);
        //экран перед
        addQuad(vertices, facets,
                xFactor + 20,                yFactor, zFactor,
                xFactor + 20, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + 20, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor + 20,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);
        //экран верх
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor + 20, yFactor + modelHeight * SCALE_FACTOR, zFactor + countFloors * SCALE_FACTOR/2,
                xFactor + 20,                yFactor, zFactor + countFloors * SCALE_FACTOR/2);
        //экран низ
        addQuad(vertices, facets,
                xFactor,                yFactor, zFactor,
                xFactor, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + 20, yFactor + modelHeight * SCALE_FACTOR, zFactor,
                xFactor + 20,                yFactor, zFactor);
    }

//   //стены шкафа
//    for (int i = 0; i < countFloors; i++)
//    {
//        for (int k = 0; k < 2; k++)
//        {
//            for (int j = 0; j < modelLength; j++)
//            {
//                addQuad(vertices, facets,
//                        xFactor,                yFactor, zFactor,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor,                yFactor, zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor,                yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor,                yFactor, zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor,                    yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor,                    yFactor, zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR,         yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR,         yFactor, zFactor + SCALE_FACTOR,
//                        xFactor + SCALE_FACTOR, yFactor, zFactor + SCALE_FACTOR);

//                xFactor += SCALE_FACTOR;
//            }

//            xFactor = xCell * SCALE_FACTOR + 10;
//            yFactor += SCALE_FACTOR * modelHeight;
//        }

//        yFactor = yCell * SCALE_FACTOR + 10;


//        for (int k = 0; k < 2; k++)
//        {
//            for (int j = 0; j < modelHeight; j++)
//            {
//                addQuad(vertices, facets,
//                       xFactor, yFactor,                zFactor,
//                       xFactor, yFactor + SCALE_FACTOR, zFactor,
//                       xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                       xFactor, yFactor,                zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor, yFactor,                zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                        xFactor, yFactor,                zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor, yFactor,                    zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                        xFactor, yFactor,                    zFactor + SCALE_FACTOR);
//                addQuad(vertices, facets,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR,         zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR,         zFactor + SCALE_FACTOR,
//                        xFactor, yFactor + SCALE_FACTOR, zFactor + SCALE_FACTOR);

//                yFactor += SCALE_FACTOR;
//            }

//            yFactor = yCell * SCALE_FACTOR + 10;
//            xFactor += SCALE_FACTOR * modelLength;
//        }

//        xFactor = xCell * SCALE_FACTOR + 10;

//        zFactor += SCALE_FACTOR;
//    }

//    addQuad(vertices, facets,
//            xFactor,         yFactor,     zFactor,
//            xFactor + 2 * SCALE_FACTOR,         yFactor,                                  zFactor,
//            xFactor + 2 * SCALE_FACTOR, yFactor + 1 * SCALE_FACTOR, zFactor,
//            xFactor, yFactor + 1 * SCALE_FACTOR, zFactor);
    PolModel tvModel(vertices, facets, "Телевизор");
    tvModel.setUsedCell(xCell, yCell);
    tvModel.setHeightModel(modelHeight);
    tvModel.setWidthModel(modelLength);
    tvModel.setBoardHeight(countFloors);
    tvModel.setDirectionModel(direction);
    tvModel.setModelType(PolModel::Tv);
    tvModel.setModelNum(scene->getModelsNum());
    scene->addModel(tvModel);
}

