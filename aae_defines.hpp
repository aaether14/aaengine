#ifndef AAE_DEFINES_HPP
#define AAE_DEFINES_HPP



/**
*This header file will contain definitions that affect certain features of the engine
*/



/**
*Defining this will compile against fbx sdk allowing user to load fbx models
*and convert them to aaem
*/
//#define AAE_USING_FBX


/**
*Defining this will allow user to read what opengl error server issues
*/
//#define AAE_USING_OPENGL_DEBUG
#ifdef AAE_USING_OPENGL_DEBUG
/**
*Defining this will ban opengl notifications of low severity
*/
#define AAE_BAN_NOTIFICATION_SEVERITY
#endif



/**
*Defining this will redirect all console messages to in-game console
*/
#define AAE_REDIRECT_MESSAGES_TO_INGAME_CONSOLE




/**
*Defining this will use the alternative worker thread for parallel loading
*/
//#define AAE_USE_ALTERNATIVE_WORKER_THREAD



#endif // AAE_DEFINES_HPP
