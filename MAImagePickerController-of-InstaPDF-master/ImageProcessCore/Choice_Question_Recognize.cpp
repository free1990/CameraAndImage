#include "Choice_Question_Recognize.h"

#include<time.h>
using namespace std;


//自定义排序函数
bool SortBy_Max_(  Thoushould_Location& A, Thoushould_Location & B)//注意：本函数的参数的类型一定要与vector中元素的类型一致
{
    return A.Thoushould > B.Thoushould;//升序排列
}

Choice_Question_Recognize::Choice_Question_Recognize()
{
    
}


Choice_Question_Recognize::~Choice_Question_Recognize()
{
    
}


void Judge_Choice_Option(Mat& Input ,vector<Rect> Rect_List ,Vector<bool> Result_Chioce)
{
    
    
    
    
    
    
}

void Choice_Question_Recognize::Judgement_Nessary(Exam_Paper_Analysis* &point_information)
{
    
    // Four Rect around the choice Question
    Rect leftRect(point_information->Question_Location_point[0][0].x,point_information->Question_Location_point[0][0].y,point_information->Question_width,point_information->Question_height);
    Rect rightRect(point_information->Question_Location_point[1][0].x,point_information->Question_Location_point[1][0].y,point_information->Question_width,point_information->Question_height);
    Rect leftRectBottom(point_information->Question_Location_point[0][1].x,point_information->Question_Location_point[0][1].y,point_information->Question_width,point_information->Question_height);
    Rect rightRectBottom(point_information->Question_Location_point[1][1].x,point_information->Question_Location_point[1][1].y,point_information->Question_width,point_information->Question_height);
    
    // set the offset project to the Source_Image
    Rect leftRect_Set_Off(leftRect.x-2*point_information->Question_width ,leftRect.y-6*point_information->Question_height,0,0);
    Rect Rightbottem_Set_Off(rightRectBottom.x+2*point_information->Question_width ,rightRectBottom.y+6*point_information->Question_height,0,0);
    
    // Set the ROI of the input image
    Rect Interst_ROI( leftRect_Set_Off.x,leftRect_Set_Off.y,Rightbottem_Set_Off.x-leftRect_Set_Off.x,Rightbottem_Set_Off.y-leftRect_Set_Off.y);
    
    Mat RGB_Interst_Image;RGB_Interst_Image.create(Interst_ROI.height,Interst_ROI.width,CV_8UC3);
    Image_basic_function::Copy_Image(point_information->Fit_Change_image,RGB_Interst_Image,Interst_ROI);
    
    // convert to gray and make a guass temple to the input image
    Mat Gray_Interst_Image,Binary_Interst_Image;
    cvtColor(RGB_Interst_Image, Gray_Interst_Image, CV_RGB2GRAY);
    GaussianBlur(Gray_Interst_Image, Gray_Interst_Image, Size(3,3),0.5);
    Binary_Interst_Image.create(Gray_Interst_Image.rows,Gray_Interst_Image.cols,CV_8UC1);
    
    // making the top image to binary image
    FastSauvolaBinarizer * point=new FastSauvolaBinarizer(29,29,0.50,0.0);
    point->Binary_way(Gray_Interst_Image,Binary_Interst_Image);
    delete point;
    
    Image_basic_function::Show_Image(Binary_Interst_Image);
    
    Image_basic_function::Show_Image(Gray_Interst_Image);
    
    
    //Ner reference  Location in the binary Image
    imwrite("restlyp.jpg", Gray_Interst_Image);
    Rect New_left_Rect(leftRect.x-leftRect_Set_Off.x,leftRect.y-leftRect_Set_Off.y,leftRect.width,leftRect.height);
    Rect New_right_Rect(rightRect.x-leftRect_Set_Off.x,rightRect.y-leftRect_Set_Off.y,rightRect.width,rightRect.height);
    
   	Mat New_Left_rect_Image;New_Left_rect_Image.create(New_left_Rect.height,New_left_Rect.width,CV_8UC1);
    Image_basic_function::Copy_Image(Binary_Interst_Image,New_Left_rect_Image,New_left_Rect);
    
    float black_number_frist =Image_basic_function::Black_Points_Get(New_Left_rect_Image);
    Mat New_right_rect_Image;New_right_rect_Image.create(New_right_Rect.height,New_right_Rect.width,CV_8UC1);
    Image_basic_function::Copy_Image(Binary_Interst_Image,New_right_rect_Image,New_left_Rect);
    float black_number_second =Image_basic_function::Black_Points_Get(New_right_rect_Image);
    
    
    float Thousould=0.5*((black_number_frist+black_number_second)/2);
    
    cout<<"本页试卷阈值为"<<Thousould<<endl;
    float avg_atuid_height=(leftRectBottom.y-leftRect.y)/3.0;
    float avg_width=(New_right_Rect.x-New_left_Rect.x)/22.0;
    float avg_height=(New_right_Rect.y-New_left_Rect.y)/22.0;
    
    
    
    // Doing mogphy to the input image
    Mat element_MORPH_RECT= getStructuringElement(MORPH_RECT, Size(2, 1));
    Mat element_MORPH_ELLIPSE = getStructuringElement(MORPH_RECT, Size(2, 1));
    dilate(Binary_Interst_Image,Binary_Interst_Image,element_MORPH_RECT,Point(0,0),2);
    erode(Binary_Interst_Image,Binary_Interst_Image,element_MORPH_ELLIPSE,Point(0,0),2);
    
    Image_basic_function::Show_Image(Binary_Interst_Image);
    
    Mat New_Left_rect_Image_;New_Left_rect_Image_.create(New_left_Rect.height,New_left_Rect.width,CV_8UC1);
    Image_basic_function::Copy_Image(Binary_Interst_Image,New_Left_rect_Image_,New_left_Rect);
    
    float black_number_frist_ =Image_basic_function::Black_Points_Get(New_Left_rect_Image);
    
    Mat New_right_rect_Image_;New_right_rect_Image_.create(New_right_Rect.height,New_right_Rect.width,CV_8UC1);
    Image_basic_function::Copy_Image(Binary_Interst_Image,New_right_rect_Image_,New_left_Rect);
    float black_number_second_ =Image_basic_function::Black_Points_Get(New_right_rect_Image);
    float Thousould_=0.5*((black_number_frist_+black_number_second_)/2);
    char strFrame_[20];
    sprintf(strFrame_, "%d ",(int)Thousould_) ;
    putText(RGB_Interst_Image,strFrame_,cvPoint(50,15),CV_FONT_HERSHEY_SIMPLEX,0.7,CV_RGB(30,255,0));
    
    // calculate the Question sheet in the exam paper
    
    
    for (int i=1;i<22;i++)
    {
        float x=0;float y=0;
        int left_index=0;int index=0; int index_length=0;
        if (i==11)
        {
            continue;
        }
        
        if (i>=22)
        {
            
            break ;
        }
        if (i<=10)
        {
            
            cout<<i<<"题目"<<endl;
            x= New_left_Rect.x+i*avg_width;
            y=New_left_Rect.y+i*avg_height;
        }
        
        if (i>=12&&i<=21)
        {
            index =i;
            cout<<index-1<<"题目"<<endl;
            index_length=22-index;
            x=New_right_Rect.x-index_length*avg_width;
            y=New_right_Rect.y-index_length*avg_height;
        }
        
        //
        vector<Rect> Temp_ABCD;
        
        for(int j=0;j<4;j++)
        {
            Rect temp (x,y+j*avg_atuid_height,New_right_Rect.width+4,New_right_Rect.height+4);
            Temp_ABCD.push_back(temp);
            rectangle(RGB_Interst_Image,temp,CV_RGB(255,0,0));
            Mat Choice_ROI_Image;Choice_ROI_Image.create(temp.height,temp.width,CV_8UC1);
            Image_basic_function::Copy_Image(Binary_Interst_Image,Choice_ROI_Image,temp);
            int Point_Number=Image_basic_function::Black_Points_Get(Choice_ROI_Image);
            
            char strFrame[20];
            sprintf(strFrame, "%d ",Point_Number) ;
            
            if(Point_Number<Thousould_)
            {
                putText(RGB_Interst_Image,strFrame,cvPoint(temp.x,temp.y),CV_FONT_HERSHEY_SIMPLEX,0.3,CV_RGB(0,255,0));
            }
            
            else
            {
                putText(RGB_Interst_Image,strFrame,cvPoint(temp.x,temp.y),CV_FONT_HERSHEY_SIMPLEX,0.3,CV_RGB(0,0,255));
            }
            Image_basic_function::Show_Image(RGB_Interst_Image);
            
            
            cout<<Point_Number<<endl;
            
        }
        
        imwrite("result.jpg",RGB_Interst_Image);
    }
}


void Choice_Question_Recognize::Choice_Question_Algotrthm(Exam_Paper_Analysis *& ponit)
{
    
    
    // Malloc the Mat space and index space
    int Question_number =40;
    
    vector<vector<Mat>>   Question_Image_Together(Question_number,vector<Mat>());
    
    vector<vector<bool>>   Question_Choice_index_Together_Frist_Low(Question_number,vector<bool>());
    
    vector<vector<bool>>   Last_decision_Choice(Question_number,vector<bool>());
    
    vector<vector<bool>>   Question_Choice_index_Together_Second_High(Question_number,vector<bool>());
    
    vector<vector<float>> Up_Togrther(Question_number,vector<float>());;
    
    vector<vector<float>> Down_Together(Question_number,vector<float>());
    
    vector<vector<float>> Static_Black_Points(Question_number,vector<float>());
    
    float Up_Thousould =0;float Down_Thousould =0;
    
    
    //judge and collection the high thshould ,but the collection had been choiced ,Here has
    // frist 20 Questions and second 20 Questions
    
    
    
    Judgement_Frist_Low_Thousould(ponit,Question_Choice_index_Together_Frist_Low);
    Judgement_Frist_Low_Thousould_Second(ponit,Question_Choice_index_Together_Frist_Low);
    
    
    
    //Fill the Lower Thoushould determine value in the Static_Black_Points Points
    Filling_Corresponding_Location_Frist(Question_Choice_index_Together_Frist_Low,ponit,Up_Togrther,Down_Together,Static_Black_Points);
    Filling_Corresponding_Location_Second(Question_Choice_index_Together_Frist_Low,ponit,Up_Togrther,Down_Together,Static_Black_Points);
    
    //Get the flag and accurate number of the Up_Togrther and Down_Together ,record the had determined choice Questions
    Judgement_with_Prior_Knowledge(Question_Choice_index_Together_Frist_Low,Static_Black_Points,Up_Togrther,Down_Together);
    
    //Get The up_Thoushould
    vector<Thoushould_Location> Up_Thoushould_List;vector<Thoushould_Location> Down_Thoushould_List;
    Get_The_UP_List(Up_Togrther,Up_Thoushould_List);
    Get_The_Down_List(Down_Together,Down_Thoushould_List);
    
    std::sort(Up_Thoushould_List.begin(),Up_Thoushould_List.end(),SortBy_Max_);
    std::sort(Down_Thoushould_List.begin(),Down_Thoushould_List.end(),SortBy_Max_);
    
    // Up_Thshould is determine by the Last three elements
    if (Up_Thoushould_List.size()>3)
    {
        for (int index=Up_Thoushould_List.size();index>Up_Thoushould_List.size()-3;index--)
        {
            Up_Thousould+=Up_Thoushould_List[index-1].Thoushould;
            
        }
        
        Up_Thousould=Up_Thousould/3.0;
    }
    else
    {
        int max_index=Up_Thoushould_List.size();
        Up_Thousould=Up_Thoushould_List[max_index-1].Thoushould;
    }
    
    
    // Lower_Thoushould is determine by the down largest ,but it is not near to the Up_Thousould ,because it is not handle cleanly
    int times=0;
    for (int i=0;i<Down_Thoushould_List.size();i++)
    {
        
        if (abs(Down_Thoushould_List[i].Thoushould/Up_Thousould)>0.65) //存在近视值 ，可能是因为擦的不干净的原因,这里设置的条件是波动值的0.65倍数
        {
            continue;
        }
        
        Down_Thousould+=Down_Thoushould_List[i].Thoushould;
        times++;
    }
    Down_Thousould=Down_Thousould/times;
    
    
    // Redetermine the Last Choice in the Question
    
    for (int i=0;i<Static_Black_Points.size();i++)
    {
        
        for (int j=0;j<4;j++)
        {
            
            if (Static_Black_Points[i][j]>=Up_Thousould)
            {
                Last_decision_Choice[i].push_back(true);
            }
            
            if (Static_Black_Points[i][j]<Down_Thousould)
            {
                Last_decision_Choice[i].push_back(false);
            }
            
            if (Static_Black_Points[i][j]>Down_Thousould&&Static_Black_Points[i][j]<Up_Thousould)
            {
                int length_false=abs( Static_Black_Points[i][j]-Down_Thousould);
                int length_True=abs ( Static_Black_Points[i][j]-Up_Thousould);
                if (length_false<length_True)
                {
                    Last_decision_Choice[i].push_back(false);
                }
                else
                {
                    Last_decision_Choice[i].push_back(true);
                }
                
                
            }
        }
    }
    
    
    
    
    
    Show_The_Result_Of_Last_Decision_UP(ponit,Last_decision_Choice);
    Show_The_Result_Of_Last_Decision_DOWN(ponit,Last_decision_Choice);
    
}



void Choice_Question_Recognize:: Red_Points_analysis(Exam_Paper_Analysis *& point_information)
{
    
    
    
    Rect leftRect(point_information->Question_Location_point[0][3].x,point_information->Question_Location_point[0][3].y,point_information->Question_width,point_information->Question_height);
    Rect rightRect(point_information->Question_Location_point[1][3].x,point_information->Question_Location_point[1][3].y,point_information->Question_width,point_information->Question_height);
    
    
    //Set the offset project to the Source_Image
    Rect leftRect_Set_Off(leftRect.x-2*point_information->Question_width ,leftRect.y-6*point_information->Question_height,0,0);
    Rect Rightbottem_Set_Off(rightRect.x+2*point_information->Question_width ,rightRect.y+6*point_information->Question_height,0,0);
    
    // Set the ROI of the input image
    Rect Interst_ROI( leftRect_Set_Off.x,leftRect_Set_Off.y,Rightbottem_Set_Off.x-leftRect_Set_Off.x,Rightbottem_Set_Off.y-leftRect_Set_Off.y);
    
    Mat RGB_Interst_Image;RGB_Interst_Image.create(Interst_ROI.height,Interst_ROI.width,CV_8UC3);
    Image_basic_function::Copy_Image(point_information->Fit_Change_image,RGB_Interst_Image,Interst_ROI);
    Image_basic_function::Show_Image(RGB_Interst_Image);
    
    // Get the left and right points of the Black
    Rect New_left_Rect(leftRect.x-leftRect_Set_Off.x,leftRect.y-leftRect_Set_Off.y,leftRect.width,leftRect.height);
    Rect New_right_Rect(rightRect.x-leftRect_Set_Off.x,rightRect.y-leftRect_Set_Off.y,rightRect.width,rightRect.height);
    
    float avg_width=(New_right_Rect.x-New_left_Rect.x)/22.0;
    float avg_height=(New_right_Rect.y-New_left_Rect.y)/22.0;
    
    
    //char strFrame_[20];
    //sprintf(strFrame_, "%d ",(int)Thousould_) ;
    //putText(RGB_Interst_Image,strFrame_,cvPoint(50,15),CV_FONT_HERSHEY_SIMPLEX,0.7,CV_RGB(30,255,0));
    
    for (int i=1;i<22;i++)
    {
        int index=0;
        float x=0;float y=0;
        int left_index=0; int index_length=0;
        if (i==11)
        {
            continue;
        }
        
        if (i>=22)
        {
            
            break ;
        }
        
        
        if (i<=10)
        {
            index=i;
            cout<<index<<"题目"<<endl;
            x= New_left_Rect.x+i*avg_width;
            y=New_left_Rect.y+i*avg_height;
        }
        
        if (i>=12&&i<=21)
        {
            index =i;
            cout<<index<<"题目"<<endl;
            index_length=22-index;
            x=New_right_Rect.x-index_length*avg_width;
            y=New_right_Rect.y-index_length*avg_height;
        }
        
        Rect temp (x,y,New_right_Rect.width+4,New_right_Rect.height+4);
        Mat Choice_ROI_Image;Choice_ROI_Image.create(temp.height,temp.width,CV_8UC3);
        Image_basic_function::Copy_Image(RGB_Interst_Image,Choice_ROI_Image,temp);
        
        int Red_Together=Image_basic_function::Red_Together_Points_Get(Choice_ROI_Image);
        int Red_Points=Image_basic_function::Red_Points_Get(Choice_ROI_Image,false);
        
        char strFrame1[20],strFrame2[20];
        sprintf(strFrame1, "%d ",Red_Together) ;
        sprintf(strFrame2, "%d ",Red_Points) ;
        
        putText(RGB_Interst_Image,strFrame2,cvPoint(temp.x,temp.y-9),CV_FONT_HERSHEY_SIMPLEX,0.3,CV_RGB(0,255,0));
        putText(RGB_Interst_Image,strFrame1,cvPoint(temp.x,temp.y-3),CV_FONT_HERSHEY_SIMPLEX,0.3,CV_RGB(0,255,0));
        rectangle(RGB_Interst_Image,temp,CV_RGB(255,0,0));
        Image_basic_function::Show_Image(RGB_Interst_Image);
    }
}





void Choice_Question_Recognize::Judgement_Frist_Low_Thousould(Exam_Paper_Analysis *& point_information,vector<vector<bool>>&  Question_Choice_index_Together_Frist_Low)
{
    
    Rect leftRect(point_information->Question_Location_point[0][0].x,point_information->Question_Location_point[0][0].y,point_information->Question_width,point_information->Question_height);
    Rect rightRect(point_information->Question_Location_point[1][0].x,point_information->Question_Location_point[1][0].y,point_information->Question_width,point_information->Question_height);
    Rect leftRectBottom(point_information->Question_Location_point[0][1].x,point_information->Question_Location_point[0][1].y,point_information->Question_width,point_information->Question_height);
    Rect rightRectBottom(point_information->Question_Location_point[1][1].x,point_information->Question_Location_point[1][1].y,point_information->Question_width,point_information->Question_height);
    
    //Set the offset project to the Source_Image
    Rect leftRect_Set_Off(leftRect.x-2*point_information->Question_width ,leftRect.y-6*point_information->Question_height,0,0);
    Rect Rightbottem_Set_Off(rightRectBottom.x+2*point_information->Question_width ,rightRectBottom.y+6*point_information->Question_height,0,0);
    
    // Set the ROI of the input image
    Rect Interst_ROI( leftRect_Set_Off.x,leftRect_Set_Off.y,Rightbottem_Set_Off.x-leftRect_Set_Off.x,Rightbottem_Set_Off.y-leftRect_Set_Off.y);
    
    Mat RGB_Interst_Image;RGB_Interst_Image.create(Interst_ROI.height,Interst_ROI.width,CV_8UC3);
    Image_basic_function::Copy_Image(point_information->Fit_Change_image,RGB_Interst_Image,Interst_ROI);
    
    // convert to gray and make a guass temple to the input image
    Mat Gray_Interst_Image,Binary_Interst_Image;
    cvtColor(RGB_Interst_Image, Gray_Interst_Image, CV_RGB2GRAY);
    Image_basic_function::Show_Image(Gray_Interst_Image);
    
    // making the top image to binary image
    Binary_Interst_Image.create(Gray_Interst_Image.rows,Gray_Interst_Image.cols,CV_8UC1);
    FastSauvolaBinarizer * point=new FastSauvolaBinarizer(29,29,0.4,0.0);
    point->Binary_way(Gray_Interst_Image,Binary_Interst_Image);
    delete point;
    Image_basic_function::Show_Image(Binary_Interst_Image);
    
    // making mogphy to the binary image
    Mat element_MORPH_RECT= getStructuringElement(MORPH_RECT, Size(2, 1));
    Mat element_MORPH_ELLIPSE = getStructuringElement(MORPH_RECT, Size(2, 1));
    dilate(Binary_Interst_Image,Binary_Interst_Image,element_MORPH_RECT,Point(0,0),2);
    erode(Binary_Interst_Image,Binary_Interst_Image,element_MORPH_ELLIPSE,Point(0,0),2);
    Image_basic_function::Show_Image(Binary_Interst_Image);
    
    
    // Get the left and right points of the Black
    Rect New_left_Rect(leftRect.x-leftRect_Set_Off.x,leftRect.y-leftRect_Set_Off.y,leftRect.width,leftRect.height);
    Rect New_right_Rect(rightRect.x-leftRect_Set_Off.x,rightRect.y-leftRect_Set_Off.y,rightRect.width,rightRect.height);
    
    
    Rect  whole_New_left_Rect(New_left_Rect.x-3,New_left_Rect.y-3,New_left_Rect.width+6,New_left_Rect.height+6);
    
    Mat New_Left_rect_Image_;New_Left_rect_Image_.create(whole_New_left_Rect.height,whole_New_left_Rect.width,CV_8UC1);
    Image_basic_function::Copy_Image(Binary_Interst_Image,New_Left_rect_Image_,whole_New_left_Rect);
    float black_number_frist_ =Image_basic_function::Black_Points_Get(New_Left_rect_Image_);
    
    
    
    Rect  whole_New_right_Rect(New_right_Rect.x-3,New_right_Rect.y-3,New_right_Rect.width+6,New_right_Rect.height+6);
    Mat New_right_rect_Image_;New_right_rect_Image_.create(whole_New_right_Rect.height,whole_New_right_Rect.width,CV_8UC1);
    Image_basic_function::Copy_Image(Binary_Interst_Image,New_right_rect_Image_,whole_New_right_Rect);
    float black_number_second_ =Image_basic_function::Black_Points_Get(New_right_rect_Image_);
    
    
    // get the average of the left and right black points
    float Thousould_=0.5*((black_number_frist_+black_number_second_)/2.0);
    
    
    float avg_atuid_height=(leftRectBottom.y-leftRect.y)/3.0;
    float avg_width=(New_right_Rect.x-New_left_Rect.x)/22.0;
    float avg_height=(New_right_Rect.y-New_left_Rect.y)/22.0;
    
    
    char strFrame_[20];
    sprintf(strFrame_, "%d ",(int)Thousould_) ;
    putText(RGB_Interst_Image,strFrame_,cvPoint(50,15),CV_FONT_HERSHEY_SIMPLEX,0.7,CV_RGB(30,255,0));
    
    // calculate the Question sheet in the exam paper
    
    rectangle(RGB_Interst_Image,whole_New_left_Rect,CV_RGB(255,0,0));
    rectangle(RGB_Interst_Image,whole_New_right_Rect,CV_RGB(255,0,0));
    
    for (int i=1;i<22;i++)
    {
        int index=0;
        float x=0;float y=0;
        int left_index=0; int index_length=0;
        if (i==11)
        {
            continue;
        }
        
        if (i>=22)
        {
            
            break ;
        }
        
        
        if (i<=10)
        {
            index=i;
            cout<<index<<"题目"<<endl;
            x= New_left_Rect.x+i*avg_width;
            y=New_left_Rect.y+i*avg_height;
        }
        
        if (i>=12&&i<=21)
        {
            index =i;
            cout<<index<<"题目"<<endl;
            index_length=22-index;
            x=New_right_Rect.x-index_length*avg_width;
            y=New_right_Rect.y-index_length*avg_height;
        }
        
        //
        vector<Rect> Temp_ABCD;
        
        for(int j=0;j<4;j++)
        {
            Rect temp (x,y+j*avg_atuid_height,New_right_Rect.width+4,New_right_Rect.height+4);
            Temp_ABCD.push_back(temp);
            rectangle(RGB_Interst_Image,temp,CV_RGB(255,0,0));
            Mat Choice_ROI_Image;Choice_ROI_Image.create(temp.height,temp.width,CV_8UC1);
            Image_basic_function::Copy_Image(Binary_Interst_Image,Choice_ROI_Image,temp);
            int Point_Number=Image_basic_function::Black_Points_Get(Choice_ROI_Image);
            
            char strFrame[20];
            sprintf(strFrame, "%d ",Point_Number) ;
            
            if(Point_Number<Thousould_)
            {
                putText(RGB_Interst_Image,strFrame,cvPoint(temp.x,temp.y),CV_FONT_HERSHEY_SIMPLEX,0.3,CV_RGB(0,255,0));
                
                if (index<12)
                {
                    Question_Choice_index_Together_Frist_Low[index-1].push_back(0);
                }
                else
                {
                    Question_Choice_index_Together_Frist_Low[index-2].push_back(0);
                }
                
                
            }
            
            else
            {
                putText(RGB_Interst_Image,strFrame,cvPoint(temp.x,temp.y),CV_FONT_HERSHEY_SIMPLEX,0.3,CV_RGB(0,0,255));
                
                if (index<12)
                {
                    Question_Choice_index_Together_Frist_Low[index-1].push_back(1);
                }
                else
                {
                    Question_Choice_index_Together_Frist_Low[index-2].push_back(1);
                }
            }
            Image_basic_function::Show_Image(RGB_Interst_Image);
            
            cout<<Point_Number<<endl;
        }
    }
    
    //imwrite("result.jpg",RGB_Interst_Image);
}

void Choice_Question_Recognize::Judgement_Frist_Low_Thousould_Second (Exam_Paper_Analysis *& point_information,vector<vector<bool>>&  Question_Choice_index_Together_Frist_Low)
{
    
    Rect leftRect(point_information->Question_Location_point[0][2].x,point_information->Question_Location_point[0][2].y,point_information->Question_width,point_information->Question_height);
    Rect rightRect(point_information->Question_Location_point[1][2].x,point_information->Question_Location_point[1][2].y,point_information->Question_width,point_information->Question_height);
    
    Rect leftRectBottom(point_information->Question_Location_point[0][3].x,point_information->Question_Location_point[0][3].y,point_information->Question_width,point_information->Question_height);
    Rect rightRectBottom(point_information->Question_Location_point[1][3].x,point_information->Question_Location_point[1][3].y,point_information->Question_width,point_information->Question_height);
    
    //Set the offset project to the Source_Image
    Rect leftRect_Set_Off(leftRect.x-2*point_information->Question_width ,leftRect.y-6*point_information->Question_height,0,0);
    Rect Rightbottem_Set_Off(rightRectBottom.x+2*point_information->Question_width ,rightRectBottom.y+6*point_information->Question_height,0,0);
    
    // Set the ROI of the input image
    Rect Interst_ROI( leftRect_Set_Off.x,leftRect_Set_Off.y,Rightbottem_Set_Off.x-leftRect_Set_Off.x,Rightbottem_Set_Off.y-leftRect_Set_Off.y);
    
    Mat RGB_Interst_Image;RGB_Interst_Image.create(Interst_ROI.height,Interst_ROI.width,CV_8UC3);
    Image_basic_function::Copy_Image(point_information->Fit_Change_image,RGB_Interst_Image,Interst_ROI);
    
    // convert to gray and make a guass temple to the input image
    Mat Gray_Interst_Image,Binary_Interst_Image;
    cvtColor(RGB_Interst_Image, Gray_Interst_Image, CV_RGB2GRAY);
    Image_basic_function::Show_Image(Gray_Interst_Image);
    
    // making the top image to binary image
    Binary_Interst_Image.create(Gray_Interst_Image.rows,Gray_Interst_Image.cols,CV_8UC1);
    FastSauvolaBinarizer * point=new FastSauvolaBinarizer(29,29,0.4,0.0);
    point->Binary_way(Gray_Interst_Image,Binary_Interst_Image);
    delete point;
    Image_basic_function::Show_Image(Binary_Interst_Image);
    
    // making mogphy to the binary image
    Mat element_MORPH_RECT= getStructuringElement(MORPH_RECT, Size(2, 1));
    Mat element_MORPH_ELLIPSE = getStructuringElement(MORPH_RECT, Size(2, 1));
    dilate(Binary_Interst_Image,Binary_Interst_Image,element_MORPH_RECT,Point(0,0),2);
    erode(Binary_Interst_Image,Binary_Interst_Image,element_MORPH_ELLIPSE,Point(0,0),2);
    Image_basic_function::Show_Image(Binary_Interst_Image);
    
    
    // Get the left and right points of the Black
    // Get the left and right points of the Black
    Rect New_left_Rect(leftRect.x-leftRect_Set_Off.x,leftRect.y-leftRect_Set_Off.y,leftRect.width,leftRect.height);
    Rect New_right_Rect(rightRect.x-leftRect_Set_Off.x,rightRect.y-leftRect_Set_Off.y,rightRect.width,rightRect.height);
    
    
    Rect  whole_New_left_Rect(New_left_Rect.x-3,New_left_Rect.y-3,New_left_Rect.width+6,New_left_Rect.height+6);
    
    Mat New_Left_rect_Image_;New_Left_rect_Image_.create(whole_New_left_Rect.height,whole_New_left_Rect.width,CV_8UC1);
    Image_basic_function::Copy_Image(Binary_Interst_Image,New_Left_rect_Image_,whole_New_left_Rect);
    float black_number_frist_ =Image_basic_function::Black_Points_Get(New_Left_rect_Image_);
    
    
    
    Rect  whole_New_right_Rect(New_right_Rect.x-3,New_right_Rect.y-3,New_right_Rect.width+6,New_right_Rect.height+6);
    Mat New_right_rect_Image_;New_right_rect_Image_.create(whole_New_right_Rect.height,whole_New_right_Rect.width,CV_8UC1);
    Image_basic_function::Copy_Image(Binary_Interst_Image,New_right_rect_Image_,whole_New_right_Rect);
    float black_number_second_ =Image_basic_function::Black_Points_Get(New_right_rect_Image_);
    
    float Thousould_=0.5*((black_number_frist_+black_number_second_)/2);
    
    
    float avg_atuid_height=(leftRectBottom.y-leftRect.y)/3.0;
    float avg_width=(New_right_Rect.x-New_left_Rect.x)/22.0;
    float avg_height=(New_right_Rect.y-New_left_Rect.y)/22.0;
    
    
    char strFrame_[20];
    sprintf(strFrame_, "%d ",(int)Thousould_) ;
    putText(RGB_Interst_Image,strFrame_,cvPoint(50,15),CV_FONT_HERSHEY_SIMPLEX,0.7,CV_RGB(30,255,0));
    
    // calculate the Question sheet in the exam paper
    
    rectangle(RGB_Interst_Image,New_left_Rect,CV_RGB(255,0,0));
    rectangle(RGB_Interst_Image,New_right_Rect,CV_RGB(255,0,0));
    for (int i=1;i<22;i++)
    {
        int index=0;
        float x=0;float y=0;
        int left_index=0; int index_length=0;
        if (i==11)
        {
            continue;
        }
        
        if (i>=22)
        {
            
            break ;
        }
        
        
        if (i<=10)
        {
            index=i;
            cout<<index<<"题目"<<endl;
            x= New_left_Rect.x+i*avg_width;
            y=New_left_Rect.y+i*avg_height;
        }
        
        if (i>=12&&i<=21)
        {
            index =i;
            cout<<index<<"题目"<<endl;
            index_length=22-index;
            x=New_right_Rect.x-index_length*avg_width;
            y=New_right_Rect.y-index_length*avg_height;
        }
        
        //
        vector<Rect> Temp_ABCD;
        
        for(int j=0;j<4;j++)
        {
            Rect temp (x,y+j*avg_atuid_height,New_right_Rect.width+4,New_right_Rect.height+4);
            Temp_ABCD.push_back(temp);
            rectangle(RGB_Interst_Image,temp,CV_RGB(255,0,0));
            Mat Choice_ROI_Image;Choice_ROI_Image.create(temp.height,temp.width,CV_8UC1);
            Image_basic_function::Copy_Image(Binary_Interst_Image,Choice_ROI_Image,temp);
            int Point_Number=Image_basic_function::Black_Points_Get(Choice_ROI_Image);
            
            char strFrame[20];
            sprintf(strFrame, "%d ",Point_Number) ;
            
            if(Point_Number<Thousould_)
            {
                putText(RGB_Interst_Image,strFrame,cvPoint(temp.x,temp.y),CV_FONT_HERSHEY_SIMPLEX,0.3,CV_RGB(0,255,0));
                
                if (index<12)
                {
                    Question_Choice_index_Together_Frist_Low[index-1+20].push_back(0);
                }
                else
                {
                    Question_Choice_index_Together_Frist_Low[index-2+20].push_back(0);
                }
                
                
            }
            
            else
            {
                putText(RGB_Interst_Image,strFrame,cvPoint(temp.x,temp.y),CV_FONT_HERSHEY_SIMPLEX,0.3,CV_RGB(0,0,255));
                
                if (index<12)
                {
                    Question_Choice_index_Together_Frist_Low[index-1+20].push_back(1);
                }
                else
                {
                    Question_Choice_index_Together_Frist_Low[index-2+20].push_back(1);
                }
            }
            Image_basic_function::Show_Image(RGB_Interst_Image);
            
            cout<<Point_Number<<endl;
        }
    }
    
    imwrite("result.jpg",RGB_Interst_Image);
}



void Choice_Question_Recognize::Filling_Corresponding_Location_Frist(vector<vector<bool>> &Question_Choice_index_Together_Frist_Low,
                                                                     Exam_Paper_Analysis *&point_information,
                                                                     vector<vector<float>>& Up_Togrther,
                                                                     vector<vector<float>>& Down_Together,
                                                                     vector<vector<float>>&  Static_Black_Points )
{
    
    Rect leftRect(point_information->Question_Location_point[0][0].x,point_information->Question_Location_point[0][0].y,point_information->Question_width,point_information->Question_height);
    Rect rightRect(point_information->Question_Location_point[1][0].x,point_information->Question_Location_point[1][0].y,point_information->Question_width,point_information->Question_height);
    Rect leftRectBottom(point_information->Question_Location_point[0][1].x,point_information->Question_Location_point[0][1].y,point_information->Question_width,point_information->Question_height);
    Rect rightRectBottom(point_information->Question_Location_point[1][1].x,point_information->Question_Location_point[1][1].y,point_information->Question_width,point_information->Question_height);
    
    //Set the offset project to the Source_Image
    Rect leftRect_Set_Off(leftRect.x-2*point_information->Question_width ,leftRect.y-6*point_information->Question_height,0,0);
    Rect Rightbottem_Set_Off(rightRectBottom.x+2*point_information->Question_width ,rightRectBottom.y+6*point_information->Question_height,0,0);
    
    // Set the ROI of the input image
    Rect Interst_ROI( leftRect_Set_Off.x,leftRect_Set_Off.y,Rightbottem_Set_Off.x-leftRect_Set_Off.x,Rightbottem_Set_Off.y-leftRect_Set_Off.y);
    
    Mat RGB_Interst_Image;RGB_Interst_Image.create(Interst_ROI.height,Interst_ROI.width,CV_8UC3);
    Image_basic_function::Copy_Image(point_information->Fit_Change_image,RGB_Interst_Image,Interst_ROI);
    
    
    
    
    
    // convert to gray and make a guass temple to the input image
    Mat Gray_Interst_Image,Binary_Interst_Image;
    cvtColor(RGB_Interst_Image, Gray_Interst_Image, CV_RGB2GRAY);
    Image_basic_function::Show_Image(Gray_Interst_Image);
    
    
    Mat canny_image;
    Canny(Gray_Interst_Image,canny_image,40,400);
    
    Image_basic_function::Show_Image(canny_image);
    
    
    // making the top image to binary image
    Binary_Interst_Image.create(Gray_Interst_Image.rows,Gray_Interst_Image.cols,CV_8UC1);
    FastSauvolaBinarizer * point=new FastSauvolaBinarizer(29,29,0.2,0.0);
    point->Binary_way(Gray_Interst_Image,Binary_Interst_Image);
    delete point;
    
    Image_basic_function::Show_Image(Binary_Interst_Image);
    
    // Get the left and right points of the Black
    Rect New_left_Rect(leftRect.x-leftRect_Set_Off.x,leftRect.y-leftRect_Set_Off.y,leftRect.width,leftRect.height);
    Rect New_right_Rect(rightRect.x-leftRect_Set_Off.x,rightRect.y-leftRect_Set_Off.y,rightRect.width,rightRect.height);
    
    
    float avg_atuid_height=(leftRectBottom.y-leftRect.y)/3.0;
    float avg_width=(New_right_Rect.x-New_left_Rect.x)/22.0;
    float avg_height=(New_right_Rect.y-New_left_Rect.y)/22.0;
    
    
    
    // calculate the Question sheet in the exam paper
    for (int i=1;i<22;i++)
    {
        int index=0;
        float x=0;float y=0;
        int left_index=0; int index_length=0;
        if (i==11)
        {
            continue;
        }
        
        if (i>=22)
        {
            
            break ;
        }
        
        
        if (i<=10)
        {
            index=i;
            cout<<index<<"题目"<<endl;
            x= New_left_Rect.x+i*avg_width;
            y=New_left_Rect.y+i*avg_height;
        }
        
        if (i>=12&&i<=21)
        {
            index =i;
            cout<<index<<"题目"<<endl;
            index_length=22-index;
            x=New_right_Rect.x-index_length*avg_width;
            y=New_right_Rect.y-index_length*avg_height;
        }
        
        //
        vector<Rect> Temp_ABCD;
        
        for(int j=0;j<4;j++)
        {
            Rect temp (x,y+j*avg_atuid_height,New_right_Rect.width+4,New_right_Rect.height+4);
            Temp_ABCD.push_back(temp);
            rectangle(RGB_Interst_Image,temp,CV_RGB(255,0,0));
            Mat Choice_ROI_Image;Choice_ROI_Image.create(temp.height,temp.width,CV_8UC1);
            Image_basic_function::Copy_Image(Binary_Interst_Image,Choice_ROI_Image,temp);
            int Point_Number=Image_basic_function::Black_Points_Get(Choice_ROI_Image);
            if (index<12)
            {
                Static_Black_Points[index-1].push_back(Point_Number);
            }
            else
            {
                Static_Black_Points[index-2].push_back(Point_Number);
            }
        }
    }
}

void Choice_Question_Recognize::Filling_Corresponding_Location_Second(vector<vector<bool>> &Question_Choice_index_Together_Frist_Low,
                                                                      Exam_Paper_Analysis *&point_information,
                                                                      vector<vector<float>>& Up_Togrther,
                                                                      vector<vector<float>>& Down_Together,
                                                                      vector<vector<float>>& Static_Black_Points)
{
    
    Rect leftRect(point_information->Question_Location_point[0][2].x,point_information->Question_Location_point[0][2].y,point_information->Question_width,point_information->Question_height);
    Rect rightRect(point_information->Question_Location_point[1][2].x,point_information->Question_Location_point[1][2].y,point_information->Question_width,point_information->Question_height);
    Rect leftRectBottom(point_information->Question_Location_point[0][3].x,point_information->Question_Location_point[0][3].y,point_information->Question_width,point_information->Question_height);
    Rect rightRectBottom(point_information->Question_Location_point[1][3].x,point_information->Question_Location_point[1][3].y,point_information->Question_width,point_information->Question_height);
    
    //Set the offset project to the Source_Image
    Rect leftRect_Set_Off(leftRect.x-2*point_information->Question_width ,leftRect.y-6*point_information->Question_height,0,0);
    Rect Rightbottem_Set_Off(rightRectBottom.x+2*point_information->Question_width ,rightRectBottom.y+6*point_information->Question_height,0,0);
    
    // Set the ROI of the input image
    Rect Interst_ROI( leftRect_Set_Off.x,leftRect_Set_Off.y,Rightbottem_Set_Off.x-leftRect_Set_Off.x,Rightbottem_Set_Off.y-leftRect_Set_Off.y);
    
    Mat RGB_Interst_Image;RGB_Interst_Image.create(Interst_ROI.height,Interst_ROI.width,CV_8UC3);
    Image_basic_function::Copy_Image(point_information->Fit_Change_image,RGB_Interst_Image,Interst_ROI);
    
    // convert to gray and make a guass temple to the input image
    Mat Gray_Interst_Image,Binary_Interst_Image;
    cvtColor(RGB_Interst_Image, Gray_Interst_Image, CV_RGB2GRAY);
    Image_basic_function::Show_Image(Gray_Interst_Image);
    
    // making the top image to binary image
    Binary_Interst_Image.create(Gray_Interst_Image.rows,Gray_Interst_Image.cols,CV_8UC1);
    FastSauvolaBinarizer * point=new FastSauvolaBinarizer(29,29,0.2,0.0);
    point->Binary_way(Gray_Interst_Image,Binary_Interst_Image);
    delete point;
    
    
    Image_basic_function::Show_Image(Binary_Interst_Image);
    
    // Get the left and right points of the Black
    Rect New_left_Rect(leftRect.x-leftRect_Set_Off.x,leftRect.y-leftRect_Set_Off.y,leftRect.width,leftRect.height);
    Rect New_right_Rect(rightRect.x-leftRect_Set_Off.x,rightRect.y-leftRect_Set_Off.y,rightRect.width,rightRect.height);
    
    
    float avg_atuid_height=(leftRectBottom.y-leftRect.y)/3.0;
    float avg_width=(New_right_Rect.x-New_left_Rect.x)/22.0;
    float avg_height=(New_right_Rect.y-New_left_Rect.y)/22.0;
    
    
    
    // calculate the Question sheet in the exam paper
    for (int i=1;i<22;i++)
    {
        int index=0;
        float x=0;float y=0;
        int left_index=0; int index_length=0;
        if (i==11)
        {
            continue;
        }
        
        if (i>=22)
        {
            
            break ;
        }
        
        
        if (i<=10)
        {
            index=i;
            cout<<index<<"题目"<<endl;
            x= New_left_Rect.x+i*avg_width;
            y=New_left_Rect.y+i*avg_height;
        }
        
        if (i>=12&&i<=21)
        {
            index =i;
            cout<<index<<"题目"<<endl;
            index_length=22-index;
            x=New_right_Rect.x-index_length*avg_width;
            y=New_right_Rect.y-index_length*avg_height;
        }
        
        //
        vector<Rect> Temp_ABCD;
        
        for(int j=0;j<4;j++)
        {
            Rect temp (x,y+j*avg_atuid_height,New_right_Rect.width+4,New_right_Rect.height+4);
            Temp_ABCD.push_back(temp);
            rectangle(RGB_Interst_Image,temp,CV_RGB(255,0,0));
            Mat Choice_ROI_Image;Choice_ROI_Image.create(temp.height,temp.width,CV_8UC1);
            Image_basic_function::Copy_Image(Binary_Interst_Image,Choice_ROI_Image,temp);
            int Point_Number=Image_basic_function::Black_Points_Get(Choice_ROI_Image);
            if (index<12)
            {
                Static_Black_Points[index-1+20].push_back(Point_Number);
            }
            else
            {
                Static_Black_Points[index-2+20].push_back(Point_Number);
            }
        }
    }
    
}

void Choice_Question_Recognize::Judgement_with_Prior_Knowledge(vector<vector<bool>> & Question_Choice_index_Together_Frist_Low,
                                                               vector<vector<float>>& Static_Black_Points,
                                                               vector<vector<float>>& Up_Togrther,
                                                               vector<vector<float>>& Down_Together)
{
    
    
    for(int index=0;index<Question_Choice_index_Together_Frist_Low.size();index++)
    {
        
        
        if (Question_Choice_index_Together_Frist_Low[index][0]||
            Question_Choice_index_Together_Frist_Low[index][1]||
            Question_Choice_index_Together_Frist_Low[index][2]||
            Question_Choice_index_Together_Frist_Low[index][3])
        {
            
            for (int inner=0;inner<4;inner++)
            {
                if (Question_Choice_index_Together_Frist_Low[index][inner])
                {
                    Up_Togrther[index].push_back(Static_Black_Points[index][inner]);
                    Down_Together[index].push_back(0);
                    
                }
                else
                {
                    Up_Togrther[index].push_back(0);
                    Down_Together[index].push_back(Static_Black_Points[index][inner]);
                    
                }
                
            }
            
        }
        else
        {
            
            
            Down_Together[index].push_back(-1);
            Down_Together[index].push_back(-1);
            Down_Together[index].push_back(-1);
            Down_Together[index].push_back(-1);
            Up_Togrther[index].push_back(-1);
            Up_Togrther[index].push_back(-1);
            Up_Togrther[index].push_back(-1);
            Up_Togrther[index].push_back(-1);
            
            
        }
    }
    
    
}


void Choice_Question_Recognize::Get_The_UP_List( vector<vector<float>>&  Up_Togrther,vector<Thoushould_Location> &Up_Thoushould_List)
{
    
    Thoushould_Location Temp ;
    for (int index=0;index<Up_Togrther.size();index++)
    {
        
        if (Up_Togrther[index][0]<0&&
            Up_Togrther[index][1]<0&&
            Up_Togrther[index][2]<0&&
            Up_Togrther[index][3]<0)
        {
            
        }
        
        else
        {
            for (int inner=0;inner<4;inner++)
            {
                if (Up_Togrther[index][inner]!=0)
                {
                    Temp.Thoushould=Up_Togrther[index][inner];
                    Temp.Question_number=index;
                    Temp.Question_Choice=inner;
                    Up_Thoushould_List.push_back(Temp);
                    
                }
            }
            
        }
    }
    
}


void Choice_Question_Recognize::Get_The_Down_List(vector<vector<float>>&Down_Together, vector<Thoushould_Location> & Down_Thoushould_List)
{
    
    Thoushould_Location Temp ;
    for (int index=0;index<Down_Together.size();index++)
    {
        
        if (Down_Together[index][0]<0&&
            Down_Together[index][1]<0&&
            Down_Together[index][2]<0&&
            Down_Together[index][3]<0)
        {
            
        }
        
        else
        {
            for (int inner=0;inner<4;inner++)
            {
                if (Down_Together[index][inner]!=0)
                {
                    Temp.Thoushould=Down_Together[index][inner];
                    Temp.Question_number=index;
                    Temp.Question_Choice=inner;
                    Down_Thoushould_List.push_back(Temp);
                    
                }
            }
            
        }
    }
}



void Choice_Question_Recognize::Show_The_Result_Of_Last_Decision_UP(Exam_Paper_Analysis *& point_information,vector<vector<bool>> & Last_decision_Choice)
{
    Rect leftRect(point_information->Question_Location_point[0][0].x,point_information->Question_Location_point[0][0].y,point_information->Question_width,point_information->Question_height);
    Rect rightRect(point_information->Question_Location_point[1][0].x,point_information->Question_Location_point[1][0].y,point_information->Question_width,point_information->Question_height);
    Rect leftRectBottom(point_information->Question_Location_point[0][1].x,point_information->Question_Location_point[0][1].y,point_information->Question_width,point_information->Question_height);
    Rect rightRectBottom(point_information->Question_Location_point[1][1].x,point_information->Question_Location_point[1][1].y,point_information->Question_width,point_information->Question_height);
    
    //Set the offset project to the Source_Image 
    Rect leftRect_Set_Off(leftRect.x-2*point_information->Question_width ,leftRect.y-6*point_information->Question_height,0,0);
    Rect Rightbottem_Set_Off(rightRectBottom.x+2*point_information->Question_width ,rightRectBottom.y+6*point_information->Question_height,0,0);
    
    // Set the ROI of the input image 
    Rect Interst_ROI( leftRect_Set_Off.x,leftRect_Set_Off.y,Rightbottem_Set_Off.x-leftRect_Set_Off.x,Rightbottem_Set_Off.y-leftRect_Set_Off.y);
    
    Mat RGB_Interst_Image;RGB_Interst_Image.create(Interst_ROI.height,Interst_ROI.width,CV_8UC3);
    Image_basic_function::Copy_Image(point_information->Fit_Change_image,RGB_Interst_Image,Interst_ROI);
    
    
    
    // Get the left and right points of the Black 
    Rect New_left_Rect(leftRect.x-leftRect_Set_Off.x,leftRect.y-leftRect_Set_Off.y,leftRect.width,leftRect.height);
    Rect New_right_Rect(rightRect.x-leftRect_Set_Off.x,rightRect.y-leftRect_Set_Off.y,rightRect.width,rightRect.height);
    
    
    
    float avg_atuid_height=(leftRectBottom.y-leftRect.y)/3.0;
    float avg_width=(New_right_Rect.x-New_left_Rect.x)/22.0;
    float avg_height=(New_right_Rect.y-New_left_Rect.y)/22.0;
    
    // calculate the Question sheet in the exam paper 
    
    
    for (int i=1;i<22;i++)     
    {   
        int index=0;
        float x=0;float y=0;
        int left_index=0; int index_length=0; 
        if (i==11)
        { 
            continue;
        }
        
        if (i>=22)
        {
            
            break ;
        }
        
        
        if (i<=10)
        {   
            index=i;
            cout<<index<<"题目"<<endl;
            x= New_left_Rect.x+i*avg_width;
            y=New_left_Rect.y+i*avg_height;
        }
        
        if (i>=12&&i<=21)
        {
            index =i;
            cout<<index<<"题目"<<endl;
            index_length=22-index;
            x=New_right_Rect.x-index_length*avg_width;
            y=New_right_Rect.y-index_length*avg_height;
        }
        
        
        
        for(int j=0;j<4;j++)
        {
            Rect temp (x,y+j*avg_atuid_height,New_right_Rect.width+4,New_right_Rect.height+4);
            
            
            if (index<12)
            {
                if (Last_decision_Choice[index-1][j])
                {
                    
                    rectangle(RGB_Interst_Image,temp,CV_RGB(255,0,0));
                }
            }
            
            else
            {
                if (Last_decision_Choice[index-2][j])
                {
                    
                    rectangle(RGB_Interst_Image,temp,CV_RGB(255,0,0));
                }
                
            }
            
            Image_basic_function::Show_Image(RGB_Interst_Image);
            
        }
    }
    
    
    
    
}
void Choice_Question_Recognize::Show_The_Result_Of_Last_Decision_DOWN(Exam_Paper_Analysis *& point_information,vector<vector<bool>> & Last_decision_Choice)
{
    
    Rect leftRect(point_information->Question_Location_point[0][2].x,point_information->Question_Location_point[0][2].y,point_information->Question_width,point_information->Question_height);	
    Rect rightRect(point_information->Question_Location_point[1][2].x,point_information->Question_Location_point[1][2].y,point_information->Question_width,point_information->Question_height);
    Rect leftRectBottom(point_information->Question_Location_point[0][3].x,point_information->Question_Location_point[0][3].y,point_information->Question_width,point_information->Question_height);
    Rect rightRectBottom(point_information->Question_Location_point[1][3].x,point_information->Question_Location_point[1][3].y,point_information->Question_width,point_information->Question_height);
    
    //Set the offset project to the Source_Image 
    Rect leftRect_Set_Off(leftRect.x-2*point_information->Question_width ,leftRect.y-6*point_information->Question_height,0,0);
    Rect Rightbottem_Set_Off(rightRectBottom.x+2*point_information->Question_width ,rightRectBottom.y+6*point_information->Question_height,0,0);
    
    // Set the ROI of the input image 
    Rect Interst_ROI( leftRect_Set_Off.x,leftRect_Set_Off.y,Rightbottem_Set_Off.x-leftRect_Set_Off.x,Rightbottem_Set_Off.y-leftRect_Set_Off.y);
    
    Mat RGB_Interst_Image;RGB_Interst_Image.create(Interst_ROI.height,Interst_ROI.width,CV_8UC3);
    Image_basic_function::Copy_Image(point_information->Fit_Change_image,RGB_Interst_Image,Interst_ROI);
    
    
    
    // Get the left and right points of the Black 
    Rect New_left_Rect(leftRect.x-leftRect_Set_Off.x,leftRect.y-leftRect_Set_Off.y,leftRect.width,leftRect.height);
    Rect New_right_Rect(rightRect.x-leftRect_Set_Off.x,rightRect.y-leftRect_Set_Off.y,rightRect.width,rightRect.height);
    
    
    
    float avg_atuid_height=(leftRectBottom.y-leftRect.y)/3.0;
    float avg_width=(New_right_Rect.x-New_left_Rect.x)/22.0;
    float avg_height=(New_right_Rect.y-New_left_Rect.y)/22.0;
    
    // calculate the Question sheet in the exam paper 
    
    
    for (int i=1;i<22;i++)     
    {   
        int index=0;
        float x=0;float y=0;
        int left_index=0; int index_length=0; 
        if (i==11)
        { 
            continue;
        }
        
        if (i>=22)
        {
            
            break ;
        }
        
        
        if (i<=10)
        {   
            index=i;
            cout<<index<<"题目"<<endl;
            x= New_left_Rect.x+i*avg_width;
            y=New_left_Rect.y+i*avg_height;
        }
        
        if (i>=12&&i<=21)
        {
            index =i;
            cout<<index<<"题目"<<endl;
            index_length=22-index;
            x=New_right_Rect.x-index_length*avg_width;
            y=New_right_Rect.y-index_length*avg_height;
        }
        
        
        
        for(int j=0;j<4;j++)
        {
            Rect temp (x,y+j*avg_atuid_height,New_right_Rect.width+4,New_right_Rect.height+4);
            
            
            
            if (index<12)
            {
                if (Last_decision_Choice[index-1+20][j])
                {
                    
                    rectangle(RGB_Interst_Image,temp,CV_RGB(255,0,0));
                }
            }
            
            else
            {
                if (Last_decision_Choice[index-2+20][j])
                {
                    
                    rectangle(RGB_Interst_Image,temp,CV_RGB(255,0,0));
                }
                
            }
            
            Image_basic_function::Show_Image(RGB_Interst_Image);
            
        }
    }
    
    
}