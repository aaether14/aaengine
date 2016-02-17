#include <renderer/pipeline.hpp>




void Pipeline::AddRenderer(QString renderer_name, BaseRenderer *renderer)
{


    renderers[renderer_name] = renderer;


}



Pipeline::Pipeline(QObject *parent) : QObject(parent)
{





}



Pipeline::~Pipeline()
{


    qDeleteAll(renderers);


}
