#ifndef GL_UTIL_HPP
#define GL_UTIL_HPP



#include <QOpenGLFunctions_4_3_Core>
#include <QDataStream>



#define BUFFER_OFFSET(i) ((char *)NULL + (i))




namespace aae
{



/**
 * @brief glForceSync will stall current thread untill async opengl operations finish
 * @param sync_obj is an opengl object used to sync
 * @param timeout is the time in which the opengl operations are expected to finish
 */
inline void glForceSync(GLsync &sync_obj, GLuint64 timeout){



    /**
     * get opengl 4.3 functions from context
     */
    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();




    /**
    *Put a fence the in the device command que
    */
    sync_obj = f->glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);


    /**
    *Wait untill opengl operations finish or until timeout is reached
    */
    GLenum result = f->glClientWaitSync(sync_obj, 0, timeout);
    if (result == GL_TIMEOUT_EXPIRED || result == GL_WAIT_FAILED)
        qDebug() << "abnormal sync!";



    /**
    *Delete sync object
    */
    f->glDeleteSync(sync_obj);



}




/**
 *@brief The DrawElementsCommand struct holdes information for a single draw
 *command
 */
struct DrawElementsCommand
{
    quint32 vertexCount;
    quint32 instanceCount;
    quint32 firstIndex;
    quint32 baseVertex;
    quint32 baseInstance;
};




inline QDataStream &operator <<(QDataStream &out, const DrawElementsCommand &command)
{


    out << command.baseInstance << command.baseVertex << command.firstIndex;
    out << command.instanceCount << command.vertexCount;
    return out;


}



inline QDataStream &operator >>(QDataStream &in, DrawElementsCommand &command)
{


    in >> command.baseInstance >> command.baseVertex >> command.firstIndex;
    in >> command.instanceCount >> command.vertexCount;
    return in;


}





}








#endif // GL_UTIL_HPP
