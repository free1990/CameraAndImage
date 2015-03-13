//
//  TestOpenCVUIViewController.m
//  instaoverlay
//
//  Created by John on 15/1/8.
//  Copyright (c) 2015年 mackh ag. All rights reserved.
//

#import "TestOpenCVUIViewController.h"
#import "Macros.h"
#import "UIImage+OpenCV.h"
#import "Exam_Paper_Analysis.h"

#import "MAOpenCV.h"

using namespace cv;
@interface TestOpenCVUIViewController ()

@end

@implementation TestOpenCVUIViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.automaticallyAdjustsScrollViewInsets = NO;
    
    CGRect frame = CGRectMake(0, 64, WinSize.width, WinSize.height - 64);
    UIScrollView *scrollView = [[UIScrollView alloc] initWithFrame:frame];
    scrollView.backgroundColor = [UIColor clearColor];
    [self.view addSubview:scrollView];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"3" ofType:@"jpg"];
    const char *cpath = [path cStringUsingEncoding:NSUTF8StringEncoding];
    NSLog(@"---> %s", cpath);
    
    Mat input = imread(cpath);
    
//    Mat input = [MAOpenCV cvMatFromUIImage:[UIImage imageNamed:@"3.jpg"]];
    
//    Mat input = [UIImage toCVMat:self.sourceImage];

    // ?
    vector<int> Top_rect_information;
    Top_rect_information.push_back(1);
    Top_rect_information.push_back(1);
    Top_rect_information.push_back(1);
    Top_rect_information.push_back(1);
    
    // ?
    vector<int> Question_rect_information;
    Question_rect_information.push_back(4);
    Question_rect_information.push_back(4);
    Question_rect_information.push_back(5);
    Question_rect_information.push_back(5);
    
    // ?
    bool Is_front_page = true;
    bool Is_A3_style = true;
    int exception_mean = -1;
    
    Exam_Paper_Analysis *analysis = new Exam_Paper_Analysis();
    analysis->Paper_information_get(input, Top_rect_information, Question_rect_information, Is_front_page, Is_A3_style, exception_mean);
    
    // ?
    NSLog(@"%d", exception_mean);
    if (exception_mean == -1) {
        
        // draw the top rect location
        for (int i = 0; i < analysis->Top_Location_rect.size(); i++) {
            
            if (analysis->Top_Location_rect[i].x != 0) {
                
                rectangle(analysis->Fit_Change_image, analysis->Top_Location_rect[i], CV_RGB(0, 255, 0));
                
                DLOG(@"x--%d", analysis->Top_Location_rect[i].x);
                DLOG(@"y--%d", analysis->Top_Location_rect[i].y);
                DLOG(@"w--%d", analysis->Top_Location_rect[i].width);
                DLOG(@"h--%d\n\n", analysis->Top_Location_rect[i].height);
                
            }
        }
        
        // draw the question rect location
        for (int i = 0; i < analysis->Question_Location_point.size(); i++) {
            for (int j = 0; j < analysis->Question_Location_point[i].size(); j++) {
                
                cv::Point pt2(analysis->Question_Location_point[i][j].x + analysis->Question_width,
                              analysis->Question_Location_point[i][j].y + analysis->Question_height);
                
                rectangle(analysis->Fit_Change_image, analysis->Question_Location_point[i][j], pt2, CV_RGB(255, 0, 0));
            }
        }
        
    }
    
    UIImage *processedImage = [UIImage fromCVMat:analysis->Fit_Change_image];
    
    NSLog(@"processedImage--- %@", processedImage);
    
    CGFloat height = processedImage.size.height / processedImage.size.width * frame.size.width;
    frame = CGRectMake(0, 0, frame.size.width, height);
    
    UIImageView *imageView = [[UIImageView alloc] initWithFrame:frame];
    imageView.backgroundColor = [UIColor blueColor];
    
    imageView.image = processedImage;
    [scrollView addSubview:imageView];
    
    scrollView.contentSize = CGSizeMake(frame.size.width, height);
    
    delete analysis;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
