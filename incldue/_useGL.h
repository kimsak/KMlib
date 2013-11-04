/*
 * _useGL.h
 *
 *  Created on: 2013/02/18
 *      Author: kimurayuusaku
 */

#ifndef USEGL_H_
#define USEGL_H_

#if defined(__ANDROID__)
#include <GLES/gl.h>
#include <GLES/glext.h>

#elif defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>

#endif

#ifndef NULL
#define NULL	(0)
#endif	/* defined(NULL) */

#endif /* USEGL_H_ */
