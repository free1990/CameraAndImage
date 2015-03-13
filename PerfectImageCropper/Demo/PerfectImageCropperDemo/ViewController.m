//
//  ViewController.m
//  PerfectImageCropperDemo
//
//  Created by Magic Young on 5/29/13.
//  Copyright (c) 2013 Magic Young. All rights reserved.
//

#import "ViewController.h"
#import <QuartzCore/QuartzCore.h>
#import "../../PerfectImageCropper/ImageCropperView.h"

@interface ViewController ()

@property (nonatomic, retain) IBOutlet ImageCropperView *cropper;
@property (nonatomic, retain) IBOutlet UIImageView *result;
@property (nonatomic, retain) IBOutlet UIButton *btn;

@end

@implementation ViewController
@synthesize cropper, result, btn;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    cropper.layer.borderWidth = 1.0;
    cropper.layer.borderColor = [UIColor blueColor].CGColor;
    [cropper setup];
    cropper.image = [UIImage imageNamed:@"beauty.jpeg"];
    
    [btn addTarget:self action:@selector(buttonClicked) forControlEvents:UIControlEventTouchUpInside];
}

- (void)buttonClicked
{
    if ([btn.currentTitle isEqualToString:@"Crop"]) {
        [cropper finishCropping];
        result.image = cropper.croppedImage;
        cropper.hidden = YES;
        [btn setTitle:@"Back" forState:UIControlStateNormal];
        [btn setTitle:@"Back" forState:UIControlStateHighlighted];
    }else
    {
        [cropper reset];
        cropper.hidden = NO;
        [btn setTitle:@"Crop" forState:UIControlStateNormal];
        [btn setTitle:@"Crop" forState:UIControlStateHighlighted];
        result.image = nil;
    }
}

@end
