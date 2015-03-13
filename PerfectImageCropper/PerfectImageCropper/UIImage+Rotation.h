//
//  UIImage+Rotation.h
//  PerfectImageCropper
//
//  Created by Magic Young on 5/29/13.
//  Copyright (c) 2013 Magic Young. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIImage (Rotation)

- (UIImage *)imageRotatedByRadians:(CGFloat)radians;
- (UIImage *)imageRotatedByDegrees:(CGFloat)degrees;

@end
