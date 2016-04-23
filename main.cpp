#include <core/main_controller.hpp>
#include <QApplication>




qint32 main(qint32 argc, char *argv[])
{



    QApplication a(argc, argv);



    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 3);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
#ifdef AAE_USING_OPENGL_DEBUG
    format.setOption(QSurfaceFormat::DebugContext);
#endif
    QSurfaceFormat::setDefaultFormat(format);



    Controller w;
    w.show();



    return a.exec();




}
