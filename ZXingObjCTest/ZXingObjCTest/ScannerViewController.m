//
//  ScannerViewController.m
//  ZXingObjCTest
//
//  Created by 董禹 on 14-3-23.
//  Copyright (c) 2014年 董禹. All rights reserved.
//

#import "ScannerViewController.h"

#define SCANNER_WIDTH 200.0f

@interface ScannerViewController ()
@property (nonatomic, strong) ZXCapture * capture;
@property (nonatomic, strong) UILabel *resultLabel;
@property (nonatomic,strong) UIImageView *lineView;//扫描线
@property (nonatomic,assign) BOOL willUp;//扫描移动方向
@property (nonatomic,strong) NSTimer *timer;//扫描线定时器
@end

@implementation ScannerViewController{
    CGFloat scanner_X;
    CGFloat scanner_Y;
    CGRect viewFrame;
}
- (void)dealloc
{
    self.resultLabel=nil;
    self.capture=nil;
    [self.timer invalidate];
    self.timer=nil;
    self.lineView=nil;
}

//扫描线动画
-(void)lineAnimation{
    float y=self.lineView.frame.origin.y;
    if (y<=scanner_Y) {
        self.willUp=NO;
    }else if(y>=scanner_Y+SCANNER_WIDTH){
        self.willUp=YES;
    }
    if(self.willUp){
        y-=2;
        self.lineView.frame=CGRectMake(scanner_X, y, SCANNER_WIDTH, 2);
    }else{
        y+=2;
        self.lineView.frame=CGRectMake(scanner_X, y, SCANNER_WIDTH, 2);
    }
}

-(void)initBackgroundView{
    CGRect scannerFrame=CGRectMake(scanner_X, scanner_Y,SCANNER_WIDTH, SCANNER_WIDTH);
    float x=scannerFrame.origin.x;
    float y=scannerFrame.origin.y;
    float width=scannerFrame.size.width;
    float height=scannerFrame.size.height;
    float mainWidth=viewFrame.size.width;
    float mainHeight=viewFrame.size.height;
    
    UIView *upView=[[UIView alloc]initWithFrame:CGRectMake(0, 0, mainWidth, y)];
    UIView *leftView=[[UIView alloc]initWithFrame:CGRectMake(0, y, x, height)];
    UIView *rightView=[[UIView alloc]initWithFrame:CGRectMake(x+width, y, mainWidth-x-width, height)];
    UIView *downView=[[UIView alloc]initWithFrame:CGRectMake(0, y+height, mainWidth, mainHeight-y-height)];
    
    NSArray *viewArray=[NSArray arrayWithObjects:upView,downView,leftView,rightView, nil];
    for (UIView *view in viewArray) {
        view.backgroundColor=[UIColor colorWithRed:0 green:0 blue:0 alpha:0.5f];
        [self.view addSubview:view];
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    //扫描器初始化
    self.capture = [[ZXCapture alloc] init];
    self.capture.camera = self.capture.back;
    self.capture.focusMode = AVCaptureFocusModeContinuousAutoFocus;
    self.capture.layer.frame = self.view.bounds;
    self.capture.rotation=90.0f;//可以竖屏扫描条形码
    [self.view.layer addSublayer:self.capture.layer];
    
    //坐标初始化
    CGRect frame=self.view.frame;
    //如果是ipad，横屏，交换坐标
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad){
        viewFrame=CGRectMake(frame.origin.y, frame.origin.x, frame.size.height, frame.size.width);
    }else{
        viewFrame=self.view.frame;
    }
    CGPoint centerPoint=CGPointMake(viewFrame.size.width/2, viewFrame.size.height/2);
    //扫描框的x、y坐标
    scanner_X=centerPoint.x-(SCANNER_WIDTH/2);
    scanner_Y=centerPoint.y-(SCANNER_WIDTH/2);
    
    //半透明背景初始化
    [self initBackgroundView];
    //扫描框
    UIImageView *borderView=[[UIImageView alloc]initWithImage:[UIImage imageNamed:@"border"]];
    borderView.frame=CGRectMake(scanner_X-5, scanner_Y-5, SCANNER_WIDTH+10, SCANNER_WIDTH+10);
    [self.view addSubview:borderView];
    //扫描线
    self.lineView=[[UIImageView alloc]initWithImage:[UIImage imageNamed:@"line"]];
    self.lineView.frame=CGRectMake(scanner_X, scanner_Y, SCANNER_WIDTH, 2);
    [self.view addSubview:self.lineView];
    self.timer=[NSTimer scheduledTimerWithTimeInterval:0.02f target:self selector:@selector(lineAnimation) userInfo:nil repeats:YES];
    //菜单
    float viewHeight=viewFrame.size.height;
    float viewWidth=viewFrame.size.width;
    UIView *menuView=[[UIView alloc]initWithFrame:CGRectMake(0, viewHeight-100, viewWidth, 100)];
    menuView.backgroundColor=[UIColor colorWithRed:0 green:0 blue:0 alpha:0.6f];
    [self.view addSubview:menuView];
    
    self.resultLabel=[[UILabel alloc]initWithFrame:CGRectMake(10, 10, viewWidth-20, 40)];
    self.resultLabel.backgroundColor=[UIColor grayColor];
    [menuView addSubview:self.resultLabel];
    
    UIButton *clearBtn=[UIButton buttonWithType:UIButtonTypeCustom];
    clearBtn.frame=CGRectMake(10, 50, 100, 40);
    [clearBtn setTitle:@"重新获取" forState:UIControlStateNormal];
    [clearBtn setTitleColor:[UIColor redColor] forState:UIControlStateHighlighted];
    [clearBtn addTarget:self action:@selector(clear) forControlEvents:UIControlEventTouchUpInside];
    [menuView addSubview:clearBtn];
    
    UIButton *submitBtn=[UIButton buttonWithType:UIButtonTypeCustom];
    submitBtn.frame=CGRectMake(viewWidth-110, 50, 100, 40);
    [submitBtn setTitle:@"确定" forState:UIControlStateNormal];
    [submitBtn setTitleColor:[UIColor redColor] forState:UIControlStateHighlighted];
    [submitBtn addTarget:self action:@selector(submit) forControlEvents:UIControlEventTouchUpInside];
    [menuView addSubview:submitBtn];
}

-(void)clear{
    self.resultLabel.text=@"";
}

-(void)submit{
    NSString *codeStr=self.resultLabel.text;
    if (codeStr.length==0) {
        codeStr=@"没有内容";
    }
    [self dismissViewControllerAnimated:YES completion:^{
        [self.delegate scanResult:codeStr];
    }];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.capture.delegate = self;
    [self.timer setFireDate:[NSDate distantPast]];
}

-(void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    self.capture.delegate = nil;
    [self.timer setFireDate:[NSDate distantFuture]];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

-(NSUInteger)supportedInterfaceOrientations {
	
	// iPhone only
	if( [[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone )
		return UIInterfaceOrientationMaskPortrait;
	
	// iPad only
	return UIInterfaceOrientationMaskLandscape;
}

// Supported orientations. Customize it for your own needs
// Only valid on iOS 4 / 5. NOT VALID for iOS 6.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	// iPhone only
	if( [[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone )
		return UIInterfaceOrientationIsPortrait(interfaceOrientation);
	
	// iPad only
	// iPhone only
	return UIInterfaceOrientationIsLandscape(interfaceOrientation);
}

#pragma mark -ZXCaptureDelegate

-(void)captureResult:(ZXCapture *)capture result:(ZXResult *)result{
    [self.resultLabel performSelectorOnMainThread:@selector(setText:) withObject:result.text waitUntilDone:YES];
}

@end
