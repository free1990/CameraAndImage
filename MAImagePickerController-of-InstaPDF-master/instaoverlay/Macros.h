//
//  Macros.h
//  opencv-usage
//
//  Created by zhangkai on 1/6/15.
//  Copyright (c) 2015 FClassroom. All rights reserved.
//

#ifndef opencv_usage_Macros_h
#define opencv_usage_Macros_h

#define WinSize CGSizeMake([UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height)

/*
 * if DEBUG is not defined, or if it is 0 then
 * all DLOGXXX macros will be disabled
 *
 * if DEBUG==1 then:
 * DLOG() will be enabled
 * DLOGERROR() will be enabled
 * DLOGINFO()will be disabled
 *
 * if DEBUG==2 or higher then:
 * DLOG() will be enabled
 * DLOGERROR() will be enabled
 * DLOGINFO()will be enabled
 */
#if !defined(DEBUG) || DEBUG == 0
#define DLOG(format, ...) do {} while (0)
#define DLOGINFO(format, ...) do {} while (0)
#define DLOGERROR(format, ...) do {} while (0)

#elif DEBUG == 1
#define DLOG(format, ...) NSLog((@"%s [Line %d] " format), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define DLOGERROR(format, ...) NSLog((@"%s [Line %d] " format), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define DLOGINFO(format, ...) do {} while (0)

#elif DEBUG > 1
#define DLOG(format, ...) NSLog((@"%s [Line %d] " format), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define DLOGERROR(format, ...) NSLog((@"%s [Line %d] " format), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define DLOGINFO(format, ...) NSLog((@"%s [Line %d] " format), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#endif

#endif
