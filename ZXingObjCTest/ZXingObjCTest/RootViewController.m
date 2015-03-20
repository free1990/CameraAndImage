//
//  RootViewController.m
//  ZXingObjCTest
//
//  Created by 董禹 on 14-3-24.
//  Copyright (c) 2014年 董禹. All rights reserved.
//

#import "RootViewController.h"

@interface RootViewController ()
@property (nonatomic,strong) UILabel *textLabel;
@property (nonatomic,strong) UIButton *btn;
@end

@implementation RootViewController

-(void)click{
    ScannerViewController *svc=[[ScannerViewController alloc]init];
    svc.delegate = self;
    [self presentViewController:svc animated:YES completion:nil];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    //显示结果的label
    self.textLabel=[[UILabel alloc]initWithFrame:CGRectMake(60, 100, 200, 40)];
    [self.view addSubview:self.textLabel];
    
    self.btn=[UIButton buttonWithType:UIButtonTypeCustom];
    self.btn.frame=CGRectMake(60, 150, 200, 40);
    [self.btn setTitle:@"扫描" forState:UIControlStateNormal];
    [self.btn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [self.btn setTitleColor:[UIColor redColor] forState:UIControlStateHighlighted];
    [self.btn addTarget:self action:@selector(click) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:self.btn];
}

#pragma mark ScannerViewControllerDelegate

-(void)scanResult:(NSString *)result{
    self.textLabel.text=result;
}

@end
