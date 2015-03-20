//
//  ScannerViewController.h
//  ZXingObjCTest
//
//  Created by 董禹 on 14-3-23.
//  Copyright (c) 2014年 董禹. All rights reserved.
//

#import <ZXingObjC.h>
#import <UIKit/UIKit.h>

@protocol ScannerViewControllerDelegate <NSObject>
-(void)scanResult:(NSString *)result;
@end

@interface ScannerViewController : UIViewController<ZXCaptureDelegate>
@property (nonatomic,assign) id<ScannerViewControllerDelegate> delegate;
@end
