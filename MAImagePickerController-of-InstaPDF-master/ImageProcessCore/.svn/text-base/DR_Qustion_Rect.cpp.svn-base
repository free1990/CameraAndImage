
#include "DR_Question_Rect.h"
#include"Compressive_Harr_Feature.h"
#include "Image_basic_function.h"
#include "FastSauvolaBinarizer.h"
#include "iostream"
using namespace std;

	
DR_Question_Rect::DR_Question_Rect()
{    
	this->scale_width=0.3503;
	this->scale_height=0.4750;

	this->Question_width=0;
	this->Qustion_height=0;
}


// The entrance of detected the Quetion rect in the exam papaer   
void DR_Question_Rect::Question_Rect_Detect(Mat &Fit_Change_image,vector<Rect>&Top_Location_rect,vector<int >&Top_rect_information,vector<int>Question_rect_information,int &exception_mean)
{
	Initialize(Fit_Change_image,Top_Location_rect,Top_rect_information,Question_rect_information,exception_mean);
	bool left =0;bool right =0;
	// Frist time search with the way of the Normal_Search_Qustion_Rect
	if (exception_meaning==-1)
	{
		Normal_Search_Qustion_Rect();
		Check_Question_rect_Location();
	}
	if (exception_meaning==-1)
	{
	     return;
	}
    // Sencond time search with the way of Abnormal_normal_hem_line_Search_Qustion_Rect 
	if (exception_meaning==2)
	{  
	   Clear_relation_parament();
	   Abnormal_normal_hem_line_Search_Qustion_Rect();
	   Check_Question_rect_Location();
	}
	if (exception_meaning==-1)
	{
	    return ;
	}

	// Thrid time search with the way of Abnormal_normal_hem_line_Search_Qustion_Rect 
	if (exception_meaning==2)
	{
	   Clear_relation_parament();
	   Abnormal_abnormal_hem_line_Search_Qustion_Rect();
	   Check_Question_rect_Location_with_BOOL(left ,right);
	}
	if (exception_meaning==-1)
	{
	    return ;
	}

	// Fourth time search with the way of the Abnormal_handle_dirty_Search_Qustion_Rect ,The Max Fault tolerance is one
	// if the Fault tolerance points should increase ,The Abnormal_handle_dirty_Search_Qustion_Rect paograme should do some change 
	if (exception_meaning==2)
	{
	   Clear_relation_parament();
	   //Here the judge is from the up detecte if the left-or-right is true ,it means the detecte is occur false ,it need to redetect in the following step  
	   Abnormal_handle_dirty_Search_Qustion_Rect(left,right);
	   Check_Question_rect_Location_with_BOOL(left ,right);
       Save_The_Normal_detected_Rect_points(left,right);

	}
	if (exception_meaning==-1)
	{
	    return ;
	}

	//Fifth time search with the way of the Abnormal_One_edge_true_Qustion_Rect The step is used to dealing  the ugly student hand_diraty ,which is very similar to Question rect graphe		                                                                                                
	if (exception_meaning==2)
	{
	   Clear_relation_parament();
	   Abnormal_One_edge_true_Qustion_Rect(left,right);
	   // In the Last step ,it is need to store the had detected points of the Question Rect 
	   Store_The_Had_Dtected_Question_Points();
	   Check_Question_rect_Location();
	   exception_mean=exception_meaning;
	}
}
void DR_Question_Rect::Store_The_Had_Dtected_Question_Points()
{

	Question_Location_information;
	Wrong_Question_Location_information=vector<vector<Point>>(Top_rect_number_information.size(), vector<Point>());
	for (int i=0;i<Wrong_Question_Location_information.size();i++)
	{   
		if (Question_number_information[i]!=0)
		{
			for (int j=0;j<Question_Location_information[i].size();j++)
			{
				Wrong_Question_Location_information[i].push_back(Question_Location_information[i][j]);
			}
		}
	}
}
void DR_Question_Rect::Missing_Rect_Points_fixed(Mat &Fit_Change_image,vector<vector<Point>>&Had_vretual_Question_Points,vector<Rect>&Top_Location_rect,vector<int >&Top_rect_information,vector<int>Question_rect_information,int &exception_mean)
{   
	Initialize(Fit_Change_image,Top_Location_rect,Top_rect_information,Question_rect_information,exception_mean);
	Find_The_Exist_Question_Rect(Had_vretual_Question_Points);
	Last_Fixed_The_Virtual_Points(Fit_Change_image,Had_vretual_Question_Points);
}

void DR_Question_Rect::Find_The_Exist_Question_Rect(vector<vector<Point>>&Had_vretual_Question_Points)
{    

	// Malloc The  same size with the Had  find the virtual Question Points 
	Temp_Real_points=vector<vector<Point>>(Had_vretual_Question_Points.size(),vector<Point>());
	for(int i=0;i<Temp_Real_points.size();i++)
	{
		Temp_Real_points[i]=vector<Point>(Question_number_information[i],Point(0,0));
	}
	 // based the in_put Top_rect_number_information to detected the corresponding cocolumn Question Location  
     for (int j=0;j<Top_rect_number_information.size();j++)
	 {    
		  if (Question_number_information[j]!=0)
		  {   
			  Rect Interst_Question_Rect;  Mat Image_interst_ROI; Mat Image_interst_ROI_Gray;Mat Image_interst_ROI_Binary;
			  Get_the_complex_information_with_Rect_Binary(j ,Interst_Question_Rect,Image_interst_ROI ,Image_interst_ROI_Gray,Image_interst_ROI_Binary); 
			  //imwrite("binasr_temp.jpg",Image_interst_ROI_Binary);
		      Mat Acculate_Box_image_based_Question_WH;
			  Acculate_Box_image_based_Question_WH.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC1);
			  Box_Acculate_Get(Image_interst_ROI_Binary,Acculate_Box_image_based_Question_WH);
			  Seek_The_best_Location_by_Position_limit(Had_vretual_Question_Points,j,Interst_Question_Rect,Acculate_Box_image_based_Question_WH);
		  }
	 }
}
void DR_Question_Rect::Initialize(Mat &Fit_Change_image,vector<Rect>&Top_Location_rect,vector<int >&Top_rect_information,vector<int>Question_rect_information,int &exception_mean)
{
	// top rect location information push 
	for(int j=0;j<Top_Location_rect.size();j++)
	{
		Top_rect_Location_information.push_back(Top_Location_rect[j]);
	}

	//  top rect number information 
	for (int j=0;j<Top_rect_information.size();j++)
	{
		Top_rect_number_information.push_back(Top_rect_information[j]);
	}

	// Question number information get 
	for (int j=0;j<Question_rect_information.size();j++)
	{
		Question_number_information.push_back(Question_rect_information[j]);
	}
	// input _image clone 
	Image_Question_Location=Fit_Change_image.clone();

	//malloc the point store 
	Question_Location_information=vector<vector<Point>>(Top_Location_rect.size(), vector<Point>());;

	// exception meaning giving 
	exception_meaning=exception_mean;

	// meansure a average to get the Question width and height
	float width_all=0;float height_all=0;
	for (int j=0;j<Top_rect_Location_information.size();j++)
	{
		width_all+=Top_rect_Location_information[j].width;
		height_all+=Top_rect_Location_information[j].height; 
	}
	width_all=width_all/Top_rect_Location_information.size();
	height_all=height_all/Top_rect_Location_information.size();
	this->Question_width=width_all*this->scale_width;
	this->Qustion_height=height_all*this->scale_height;
	this->Wrong_Question_width=this->Question_width;
	this->Wrong_Qustion_height=this->Qustion_height;
}

void DR_Question_Rect::Normal_Search_Qustion_Rect()
{
	 // based the in_put Top_rect_number_information to detected the corresponding cocolumn Question Location  
     for (int j=0;j<Top_rect_number_information.size();j++)
	 {    
		  if (Question_number_information[j]!=0)
		  {   
			  Rect Interst_Question_Rect;  Mat Image_interst_ROI; Mat Image_interst_ROI_Gray;Mat Image_interst_ROI_Binary;
			  Get_the_complex_information_with_Rect_Binary(j ,Interst_Question_Rect,Image_interst_ROI ,Image_interst_ROI_Gray,Image_interst_ROI_Binary); 
			  //imwrite("binasr_temp.jpg",Image_interst_ROI_Binary);
		      Mat Acculate_Box_image_based_Question_WH;
			  Acculate_Box_image_based_Question_WH.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC1);
			  Box_Acculate_Get(Image_interst_ROI_Binary,Acculate_Box_image_based_Question_WH);
			  Seek_The_best_Location(j,Interst_Question_Rect,Acculate_Box_image_based_Question_WH);
		  }
	 
	 }
	
}
void DR_Question_Rect::Abnormal_normal_hem_line_Search_Qustion_Rect()
{

	 for (int j=0;j<Top_rect_number_information.size();j++)
	 {     
		  int Blue_Gray_numaber=0;
		  if (Question_number_information[j]!=0)
		  {   
			  Rect Interst_Question_Rect;  Mat Image_interst_ROI; Mat Image_interst_ROI_Gray;Mat Image_interst_ROI_Binary;
			  Interst_Question_Rect=Interst_Rect_Back(j);
			  Image_basic_function::Copy_Image(Image_Question_Location,Image_interst_ROI,Interst_Question_Rect,true);
			  // get the bottem of 1/6 to make a judegement ,whether have the Bule-Gray points in the input_image 
			  float H_max=185.0;float H_min=155.0;float S_max=0.48;float S_min=0.28;float V_max=0.44 ;float V_min=0.24;
			  Blue_Gray_numaber=Image_basic_function::Static_Calculate(Image_interst_ROI,H_max,H_min,S_max,S_min,V_max,V_min);
			  if(Blue_Gray_numaber>150) // it presents  that there is a hem in the paper if index 
			  {   
		         Image_basic_function::Set_Bule_Gray_to_White(Image_interst_ROI);
				 Relationship_Information_Binary(Interst_Question_Rect,Image_interst_ROI,Image_interst_ROI_Gray,Image_interst_ROI_Binary);
				 Mat Acculate_Box_image_based_Question_WH;
			     Acculate_Box_image_based_Question_WH.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC1);
			     Box_Acculate_Get(Image_interst_ROI_Binary,Acculate_Box_image_based_Question_WH);
			     Seek_The_best_Location(j,Interst_Question_Rect,Acculate_Box_image_based_Question_WH);
			  }
			  else
			  {
			     Relationship_Information_Binary(Interst_Question_Rect,Image_interst_ROI,Image_interst_ROI_Gray,Image_interst_ROI_Binary);
				 Mat Acculate_Box_image_based_Question_WH;
			     Acculate_Box_image_based_Question_WH.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC1);
			     Box_Acculate_Get(Image_interst_ROI_Binary,Acculate_Box_image_based_Question_WH);
			     Seek_The_best_Location(j,Interst_Question_Rect,Acculate_Box_image_based_Question_WH);
			  }
		  }
	 
	 }
}
void DR_Question_Rect::Abnormal_abnormal_hem_line_Search_Qustion_Rect()
{
   for (int j=0;j<Top_rect_number_information.size();j++)
   {     
		  int Blue_Gray_numaber=0;
		  if (Question_number_information[j]!=0)
		  {   
			  Rect Interst_Question_Rect;  Mat Image_interst_ROI; Mat Image_interst_ROI_Gray;Mat Image_interst_ROI_Binary;
			  Interst_Question_Rect=Interst_Rect_Back(j);
			  Image_basic_function::Copy_Image(Image_Question_Location,Image_interst_ROI,Interst_Question_Rect,true);
			  float H_max=185.0;float H_min=155.0;float S_max=0.48;float S_min=0.28;float V_max=0.44 ;float V_min=0.24;
			  Blue_Gray_numaber=Image_basic_function::Static_Calculate(Image_interst_ROI,H_max,H_min,S_max,S_min,V_max,V_min);
			  if(Blue_Gray_numaber>150) // it presents  that there is a hem in the paper if index 
			  {   
				
				 Relationship_Information_Binary(Interst_Question_Rect,Image_interst_ROI,Image_interst_ROI_Gray,Image_interst_ROI_Binary);
				 int  angle_start=0; int  angle_end=0; int rhomax=0;
				 Set_The_aangle_start_And_angle_end(j,angle_start,angle_end);
				 Mat The_Rho_space=Image_basic_function::Create_space_with_hough(Image_interst_ROI_Binary,angle_start,angle_end,rhomax);
				 //Image_basic_function::Show_Image(Image_interst_ROI_Binary);
				 Point pt1(0,0) ,pt2(0,0),pt3(0,0),pt4(0,0);
				 Find_line(pt1,pt2,pt3,pt4,The_Rho_space,rhomax,Image_interst_ROI);
				 Reverse_Pixs_With_Line(Image_interst_ROI_Binary,pt1,pt2,pt3,pt4);  //set the pixs below the points to zero 
				 //Image_basic_function::Show_Image(Image_interst_ROI_Binary);
				 Mat Acculate_Box_image_based_Question_WH;
			     Acculate_Box_image_based_Question_WH.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC1);
			     Box_Acculate_Get(Image_interst_ROI_Binary,Acculate_Box_image_based_Question_WH);
			     Seek_The_best_Location(j,Interst_Question_Rect,Acculate_Box_image_based_Question_WH);
			  }
			  else
			  {
			     Relationship_Information_Binary(Interst_Question_Rect,Image_interst_ROI,Image_interst_ROI_Gray,Image_interst_ROI_Binary);
				 Mat Acculate_Box_image_based_Question_WH;
			     Acculate_Box_image_based_Question_WH.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC1);
			     Box_Acculate_Get(Image_interst_ROI_Binary,Acculate_Box_image_based_Question_WH);
			     Seek_The_best_Location(j,Interst_Question_Rect,Acculate_Box_image_based_Question_WH);
			  }
		  }
	 }
}
void DR_Question_Rect::Abnormal_handle_dirty_Search_Qustion_Rect(bool& left ,bool& right)
{    
	// based the in_put Top_rect_number_information to detected the corresponding column Question Location  
	 Compressive_Harr_Feature Harr_featue;
	 Get_Pos_Neg_Vector(Harr_featue);
     for (int j=0;j<Top_rect_number_information.size();j++)
	 {    
		  if (Question_number_information[j]!=0)
		  {   
			  Rect Interst_Question_Rect;  Mat Image_interst_ROI; Mat Image_interst_ROI_Gray;Mat Image_interst_ROI_Binary;
			  Get_the_complex_information_with_Rect_Binary(j ,Interst_Question_Rect,Image_interst_ROI ,Image_interst_ROI_Gray,Image_interst_ROI_Binary); 
		      Mat Acculate_Box_image_based_Question_WH;
			  Acculate_Box_image_based_Question_WH.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC1);
			  Box_Acculate_Get(Image_interst_ROI_Binary,Acculate_Box_image_based_Question_WH);

			  if(left==1&&(j==0||j==1))
			  {
			      Seek_The_best_Location_With_Classifer(j,Interst_Question_Rect,Image_interst_ROI_Gray,Image_interst_ROI_Binary,Acculate_Box_image_based_Question_WH,Harr_featue);
			  }
			  if (left!=1&&(j==0||j==1))
			  {
			      Seek_The_best_Location(j,Interst_Question_Rect,Acculate_Box_image_based_Question_WH);
			  }

			  if (right==1&&(j==2||j==3))
			  {
			      Seek_The_best_Location_With_Classifer(j,Interst_Question_Rect,Image_interst_ROI_Gray,Image_interst_ROI_Binary,Acculate_Box_image_based_Question_WH,Harr_featue);
			  }

			  if (right!=1&&(j==2||j==3))
			  {
			    Seek_The_best_Location(j,Interst_Question_Rect,Acculate_Box_image_based_Question_WH);  
			  }
		  }
	 }
}
void DR_Question_Rect::Abnormal_One_edge_true_Qustion_Rect(bool& left ,bool& right)
{
	 // ulgy student --especially "beijing" student 
	 // The step i+=2 ,because once find step is in paris ,Questiuon Rect matching ,the Way is to imagenation the one edge is true ,so can map the other edge Question Rect
	 for (int j=0;j<Top_rect_number_information.size();j+=2)
	 {    
		  if (Question_number_information[j]!=0)
		  {   
			  // left indormation get 
			  Rect Left_Interst_Question_Rect;  Mat Left_Image_interst_ROI; Mat Left_Image_interst_ROI_Gray;Mat Left_Image_interst_ROI_Binary;
			  Get_the_complex_information_with_Rect_Binary(j ,Left_Interst_Question_Rect,Left_Image_interst_ROI ,Left_Image_interst_ROI_Gray,Left_Image_interst_ROI_Binary); 
		      Mat Left_Acculate_Box_image_based_Question_WH;
			  Left_Acculate_Box_image_based_Question_WH.create(Left_Interst_Question_Rect.height,Left_Interst_Question_Rect.width,CV_8UC1);
			  Box_Acculate_Get(Left_Image_interst_ROI_Binary,Left_Acculate_Box_image_based_Question_WH);
			  
			  // right information get 
			  Rect Reight_Interst_Question_Rect;  Mat Reight_Image_interst_ROI; Mat Reight_Image_interst_ROI_Gray;Mat Reight_Image_interst_ROI_Binary;
              int index=j+1;
			  Get_the_complex_information_with_Rect_Binary(index ,Reight_Interst_Question_Rect,Reight_Image_interst_ROI ,Reight_Image_interst_ROI_Gray,Reight_Image_interst_ROI_Binary); 
		      Mat Reight_Acculate_Box_image_based_Question_WH;
			  Reight_Acculate_Box_image_based_Question_WH.create(Reight_Interst_Question_Rect.height,Reight_Interst_Question_Rect.width,CV_8UC1);
			  Box_Acculate_Get(Reight_Image_interst_ROI_Binary,Reight_Acculate_Box_image_based_Question_WH);

			  if(left==true&&j==0)//left exception
			  {   
				   bool Left_Map_Right=true;bool Right_Map_Left=true; // image the Matching is true ,when the parament is be set to false ,The Matching is falling
			       Mapping_Methord_To_Find_Qusetion_Rect(j,index,Left_Acculate_Box_image_based_Question_WH,Reight_Acculate_Box_image_based_Question_WH,Left_Interst_Question_Rect,Reight_Interst_Question_Rect,Left_Map_Right);
				   if (Left_Map_Right==false)
				   {  
			
					  Clear_Corresponding_Question_Locarion_Points(j);
				      Mapping_Methord_To_Find_Qusetion_Rect(index,j,Reight_Acculate_Box_image_based_Question_WH,Left_Acculate_Box_image_based_Question_WH,Reight_Interst_Question_Rect,Left_Interst_Question_Rect,Right_Map_Left);
				   }

				   if (Right_Map_Left=false)
				   {
				      return;
				   }

			  }
			  if (left!=true&&j==0) // left normal 
			  {
			      Get_The_Have_save_Points(j);
			  }

			  if (right==true&&j==2)//right exception 
			  {
			       bool Left_Map_Right=true;bool Right_Map_Left=true; 
				  // Image_basic_function::Show_Image(Reight_Image_interst_ROI_Binary);
				  // imwrite("Reight_Image_interst_ROI_Binary.jpg",Reight_Image_interst_ROI_Binary);
				  // Image_basic_function::Show_Image(Reight_Acculate_Box_image_based_Question_WH);

			       Mapping_Methord_To_Find_Qusetion_Rect(j,index,Left_Acculate_Box_image_based_Question_WH,Reight_Acculate_Box_image_based_Question_WH,Left_Interst_Question_Rect,Reight_Interst_Question_Rect,Left_Map_Right);
				   if (Left_Map_Right==false)
				   {  
					  Clear_Corresponding_Question_Locarion_Points(j);
				      Mapping_Methord_To_Find_Qusetion_Rect(index,j,Reight_Acculate_Box_image_based_Question_WH,Left_Acculate_Box_image_based_Question_WH,Reight_Interst_Question_Rect,Left_Interst_Question_Rect,Right_Map_Left);
				   }

				   if (Right_Map_Left=false)
				   {
				      return;
				   }
			  }

			  if (right!=true&&j==2)//right normal 
			  {  
				   Get_The_Have_save_Points(j);
			  }
		  }
	 }
}
Rect DR_Question_Rect::Interst_Rect_Back(int &index )
{   
    Rect rect_Roi_get(0,0,0,0);
	if (index %2!=0)
	{   
		// The meaning is from rect's x +rect's width to make rect_Roi_get.x's setoff 
		rect_Roi_get.x=Top_rect_Location_information[index].x+0.9*Top_rect_Location_information[index].width; // Sample as Left_right rect 
		rect_Roi_get.y=Top_rect_Location_information[index].y+1.5*Top_rect_Location_information[index].height;
		rect_Roi_get.width=Top_rect_Location_information[index].width+0.2*Top_rect_Location_information[index].width;
		// here may occur over the image's width 
		if ((rect_Roi_get.x+rect_Roi_get.width)>Image_Question_Location.cols)
		{
			rect_Roi_get.width=Image_Question_Location.cols-rect_Roi_get.x-2;
		}
		rect_Roi_get.height=Image_Question_Location.rows-rect_Roi_get.y-2*Qustion_height;
	}
	else 
	{
		rect_Roi_get.x=Top_rect_Location_information[index].x-Top_rect_Location_information[index].width;
		if (rect_Roi_get.x<0)
		{
			rect_Roi_get.x=2;
		}
		rect_Roi_get.y=Top_rect_Location_information[index].y+1.5*Top_rect_Location_information[index].height;
		rect_Roi_get.width=Top_rect_Location_information[index].width+0.2*Top_rect_Location_information[index].width;
		rect_Roi_get.height=Image_Question_Location.rows-rect_Roi_get.y-2*Qustion_height;
   
	}
	return rect_Roi_get;
}

void DR_Question_Rect::Get_the_complex_information_with_Rect_Binary(int &index ,Rect & Interst_Question_Rect,Mat & Image_interst_ROI ,Mat &Image_interst_ROI_Gray,Mat &Image_interst_ROI_Binary) 
{
	Interst_Question_Rect=Interst_Rect_Back(index);
	Image_interst_ROI.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC3);
	Image_interst_ROI_Gray.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC1);
	Image_interst_ROI_Binary.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC1);
	Image_basic_function::Copy_Image(Image_Question_Location,Image_interst_ROI,Interst_Question_Rect,true);
	cvtColor(Image_interst_ROI,Image_interst_ROI_Gray,CV_RGB2GRAY);
	FastSauvolaBinarizer* point =new FastSauvolaBinarizer();
	point->Binary_way(Image_interst_ROI_Gray,Image_interst_ROI_Binary);
	delete point ;
}

void DR_Question_Rect::Relationship_Information_Binary(Rect & Interst_Question_Rect,Mat & Image_interst_ROI ,Mat &Image_interst_ROI_Gray,Mat &Image_interst_ROI_Binary)
{
	Image_interst_ROI_Gray.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC1);
	Image_interst_ROI_Binary.create(Interst_Question_Rect.height,Interst_Question_Rect.width,CV_8UC1);
	cvtColor(Image_interst_ROI,Image_interst_ROI_Gray,CV_RGB2GRAY);
	FastSauvolaBinarizer* point =new FastSauvolaBinarizer();
	point->Binary_way(Image_interst_ROI_Gray,Image_interst_ROI_Binary);
	delete point ;
}
void DR_Question_Rect::Box_Acculate_Get(Mat & Image_interst_ROI_Binary,Mat &Acculate_Box_image_based_Question_WH)
{
	Image_basic_function::Set_Image_To_255_CV_8U(Acculate_Box_image_based_Question_WH);
	Mat Intergral_image;
	Intergral_image.create(Acculate_Box_image_based_Question_WH.rows+1,Acculate_Box_image_based_Question_WH.cols+1,CV_32FC1);
	integral(Image_interst_ROI_Binary,Intergral_image,CV_32FC1);
	Width_Height_box_mapping(Intergral_image,Acculate_Box_image_based_Question_WH);
	//Image_basic_function::Show_Image(Intergral_image);

}

void DR_Question_Rect::Width_Height_box_mapping(Mat &Intergral_image,Mat &Acculate_Box_image_based_Question_WH)
{   
	for (int j=0;j<Acculate_Box_image_based_Question_WH.rows-Qustion_height;j++)
	{   
		
		unsigned char * point =Acculate_Box_image_based_Question_WH.ptr<unsigned char>(j);
		for (int i=0;i<Acculate_Box_image_based_Question_WH.cols-Question_width;i++)
		{  
		   // index the left top  point of the Intergral_image image
		   float *  point_left_top=Intergral_image.ptr<float>(j+1);
		   point_left_top+=i+1;

		   // index the right botterm of the Intergral_image image
		   float * point_right_botterm=Intergral_image.ptr<float>(j+1+Qustion_height);
		   point_right_botterm+=i+1+Question_width;

		   // index the left botterm of the Intergral_image image
		   float * point_left_botterm=Intergral_image.ptr<float>(j+1+Qustion_height);
		   point_left_botterm+=i+1;

		   // index the right top of the Intergral_image image
           float *point_right_top=Intergral_image.ptr<float>(j+1);
		   point_right_top+=i+1+Question_width;

		   float Box_Whole_acculate=*point_left_top+*point_right_botterm-*point_left_botterm-*point_right_top;

		   // Normal_the image to 0-255

		   float Normal =(Box_Whole_acculate/((Question_width+1)*(Qustion_height+1)*255.0))*255.0;

		   if(Normal<0.0)
		   {
		     Normal=0;
		   }

		   if (Normal>255.0)
		   { 
		     Normal=255;
		   }

		   * point=Normal;
		   point ++;
		
		}
	
	}
	//Image_basic_function::Show_Image(Acculate_Box_image_based_Question_WH);

}

void DR_Question_Rect::Seek_The_best_Location(int &index ,Rect & Interst_Question_Rect,Mat &Acculate_Box_image_based_Question_WH)
{

	Mat  Accluate_image_cpoy; 
	Accluate_image_cpoy=Acculate_Box_image_based_Question_WH.clone();// making a copy of the Acculate_Box_image_based_Question_WH 
                                                                     //because it may find wronging in the frist search
    Find_Question_with_Zero_Min_points(index,Accluate_image_cpoy,Interst_Question_Rect,false); 

	// it is used simple to judgement the detect points is accdate the one line ,if it is not  ,the deep algorithms is strat 
	Simple_check_with_RANSAC_To_Question_rect(index);
	if (exception_meaning==-1) // it present the detected is normal  
	{
	   return ;
	}

	// it present the simple Ransaic  OR detected Question number may be wrong at least on leaf 
	if (exception_meaning==2)
	{   
		exception_meaning=-1;
	    Mat lin_message_index,Accluate_image_cpoy_Two;
		Accluate_image_cpoy_Two=Acculate_Box_image_based_Question_WH.clone();
		Deep_check_with_RANSAC_To_Question_rect(lin_message_index,index);
		float inner_k=0;float inner_b=0;
		Get_model_by_Max_innernumber(lin_message_index,inner_k,inner_b);
		Find_Question_with_Zero_Min_points_additional_by_model(index,Accluate_image_cpoy_Two,Interst_Question_Rect,inner_k,inner_b); 	
	}

}

void DR_Question_Rect::Seek_The_best_Location_by_Position_limit(vector<vector<Point>> &Had_vretual_Question_Points,int &index,Rect & Interst_Question_Rect,Mat &Acculate_Box_image_based_Question_WH)
{
	Mat  Accluate_image_cpoy;
	Accluate_image_cpoy=Acculate_Box_image_based_Question_WH.clone();// making a copy of the Acculate_Box_image_based_Question_WH 
                                                                     //because it may find wronging in the frist search
	Find_Question_with_Zero_Min_points_by_Position_limit(Had_vretual_Question_Points,index,Accluate_image_cpoy,Interst_Question_Rect,false); 

	// Here need to make a judge whether needing to making the Question Points through The RANSAC algorithm  
	int Had_find_inner_Points=Get_The_inner_Points(index);
	if (Had_find_inner_Points>3)
	{
	   RANSAC_Alogrithem_To_Separarte_Out_Points(index);
	}
}

int DR_Question_Rect::Get_The_inner_Points(int& index)
{
	int number_inner_points=0;
	for (int i=0;i<Temp_Real_points[index].size();i++)
	{
		if(Temp_Real_points[index][i].x!=0&&Temp_Real_points[index][i].y!=0)
		{
		   number_inner_points++;
		}
	}
	return number_inner_points;
}
void DR_Question_Rect::Last_Fixed_The_Virtual_Points(Mat &Fit_Change_image,vector<vector<Point>>& Had_vretual_Question_Points)
{   
	// Generator the judgement of the set_off length  
	struct delta_X_Y_Length
	{
	   int   Delata_X;
	   int   Delata_Y;
	   float Length_Distance;
	   delta_X_Y_Length(int Delata_X1,int Delata_Y1,float Length_Distance1)
	   {
	       Delata_X=Delata_X1;
		   Delata_Y=Delata_Y1;
	       Length_Distance=Length_Distance1;
	   }
	};
	vector<vector<delta_X_Y_Length>> Statics_data(vector<vector<delta_X_Y_Length>>(Had_vretual_Question_Points.size(),vector<delta_X_Y_Length>()));
	for (int i=0;i<Had_vretual_Question_Points.size();i++)
	{
		Statics_data[i]=vector<delta_X_Y_Length>(Had_vretual_Question_Points[i].size(),delta_X_Y_Length(-1000,-1000,-1000.0));
	}
	// Fill the space of the Statics_data 
	for (int i=0;i<Statics_data.size();i++)
	{   
		Point Stand_Top(Top_rect_Location_information[i].x,Top_rect_Location_information[i].y);
		for (int j=0;j<Statics_data[i].size();j++)
		{
	       delta_X_Y_Length   Temp_data(-1000,-1000,-1000.0);

		   if (Temp_Real_points[i][j].x!=0&&Temp_Real_points[i][j].y!=0)
		   {
		       Temp_data.Delata_X=Had_vretual_Question_Points[i][j].x-Temp_Real_points[i][j].x;
			   Temp_data.Delata_Y=Had_vretual_Question_Points[i][j].y-Temp_Real_points[i][j].y;
			   Temp_data.Length_Distance=Image_basic_function::Distance_Between_Points(Stand_Top,Temp_Real_points[i][j]);
			   Statics_data[i][j]=Temp_data;
			   //cout<<Temp_data.Delata_X<<"__"<<Temp_data.Delata_Y<<"__"<<Temp_data.Length_Distance<<endl;
		   }
		   else
		   {   
			   Temp_data.Length_Distance=Image_basic_function::Distance_Between_Points(Stand_Top,Had_vretual_Question_Points[i][j]);
		       Statics_data[i][j]=Temp_data;
			   //cout<<Temp_data.Delata_X<<"__"<<Temp_data.Delata_Y<<"__"<<Temp_data.Length_Distance<<endl;
		   }
		}
	}

	// Statics the error acculate by length 
	vector<float> Scale_factor_X(Top_rect_Location_information.size(),0.0f);
	vector<float> Scale_factor_Y(Top_rect_Location_information.size(),0.0f);
	for (int i=0;i<Statics_data.size();i++)
	{   
		float Scale_Whole_Acculate_X=0;int contribute_X_Scale_factor=0;float Scale_Whole_Acculate_Y=0;int contribute_Y_Scale_factor=0;
		for (int j=0;j<Statics_data[i].size();j++)
		{
			if (abs(Statics_data[i][j].Delata_X)<12&&abs(Statics_data[i][j].Delata_Y)<12)
			{
				Scale_Whole_Acculate_X+=Statics_data[i][j].Delata_X/Statics_data[i][j].Length_Distance;
				contribute_X_Scale_factor++;

				Scale_Whole_Acculate_Y+=Statics_data[i][j].Delata_Y/Statics_data[i][j].Length_Distance;
				contribute_Y_Scale_factor++;
			}
		}
		Scale_Whole_Acculate_X=Scale_Whole_Acculate_X/contribute_X_Scale_factor;
		Scale_Whole_Acculate_Y=Scale_Whole_Acculate_Y/contribute_Y_Scale_factor;
		Scale_factor_X[i]=Scale_Whole_Acculate_X;
		Scale_factor_Y[i]=Scale_Whole_Acculate_Y;
	}

	// Fill the Missing Points by the Scale length factor 
	for (int i=0;i<Temp_Real_points.size();i++)
	{   
		for(int j=0;j<Temp_Real_points[i].size();j++)
		{
			if (Temp_Real_points[i][j].x==0||Temp_Real_points[i][j].y==0)
			{
				Point Missing_Point(0,0);
				Missing_Point.x=Had_vretual_Question_Points[i][j].x-Scale_factor_X[i]*Statics_data[i][j].Length_Distance;
				Missing_Point.y=Had_vretual_Question_Points[i][j].y-Scale_factor_Y[i]*Statics_data[i][j].Length_Distance;
				Temp_Real_points[i][j]=Missing_Point;
				//Here is need to do another function ,which is to fill the Rect ROI with black blob int the Image 
				Mat Fill_Black_ROI;Fill_Black_ROI.create(Qustion_height,Question_width,CV_8UC3);
				Image_basic_function::Set_Image_To_0_CV_8U_3Channel(Fill_Black_ROI);
				Rect Fill_Black_ROI_Rect(Missing_Point.x,Missing_Point.y,Question_width,Qustion_height);
				Image_basic_function::Copy_Image(Fill_Black_ROI,Fit_Change_image,Fill_Black_ROI_Rect,false);
			}
		}
	}

	//Project the Virtual and Real Question Points to the sorce virtual space 

	for (int i=0;i<Had_vretual_Question_Points.size();i++)
	{
		for (int j=0;j<Had_vretual_Question_Points[i].size();j++)
		{
		   Had_vretual_Question_Points[i][j]=Temp_Real_points[i][j];

		}
	}
}

void DR_Question_Rect::Seek_The_best_Location_With_Classifer(int& j,Rect& Interst_Question_Rect,Mat& Image_interst_ROI_Gray,Mat& Image_interst_ROI_Binary,Mat& Acculate_Box_image_based_Question_WH,Compressive_Harr_Feature& Harr_featue)
{   
	//A clone image to find the the TOp Rect Location  
	Mat Accluate_image_cpoy;
	Accluate_image_cpoy=Acculate_Box_image_based_Question_WH.clone(); //make a clone to find Question Rect top points 
	Find_Question_with_Simlar_parament(j,Image_interst_ROI_Gray,Image_interst_ROI_Binary,Accluate_image_cpoy,Interst_Question_Rect,Harr_featue);
}

void DR_Question_Rect::Get_Pos_Neg_Vector( Compressive_Harr_Feature &Harr_featue)
{
	// generator the input positive image 
	Mat Pos_image;Mat input_positive;
    Pos_image.create(2*Qustion_height,2*Question_width,CV_8UC1);
	for (int j=0;j<Pos_image.rows;j++)
	{
	    unsigned char *point =Pos_image.ptr<unsigned char>(j);
		for (int i=0;i<Pos_image.cols;i++)
		{
			if (i>int(0.25*Pos_image.cols)&&(i<0.75*int(Pos_image.cols))&&
				j>int(0.25*Pos_image.rows)&&(j<0.75*int(Pos_image.rows)))
			{
				*point=0;
			}
			else
			{
				*point=255;
			}
			point++;     
		}
	  
	}

	//generator the neg image of input negtive
	Mat Neg_image;Mat input_negtive;
    Neg_image.create(2*Qustion_height,2*Question_width,CV_8UC1);
	for (int j=0;j<Neg_image.rows;j++)
	{
	    unsigned char *point =Neg_image.ptr<unsigned char>(j);
		for (int i=0;i<Neg_image.cols;i++)
		{
			if (i>int(0.25*Neg_image.cols)&&(i<0.75*int(Neg_image.cols))&&
				j>int(0.25*Neg_image.rows)&&(j<0.75*int(Neg_image.rows)))
			{
				*point=255;
			}
			else
			{
				*point=0;
			}
			point++;     
		}
	  
	}
	//generator the Pos and Neg feature vector of the neg and Pos image 
	resize(Pos_image,input_positive,Size(50,25),0,0,CV_INTER_NN);
	Harr_featue.Fill_pos_vector(input_positive,false);
	resize(Neg_image,input_negtive,Size(50,25),0,0,CV_INTER_NN);
	Harr_featue.Fill_neg_vector(input_negtive,false);
}

void DR_Question_Rect::Get_Pos_Neg_Vector_Sorce_Temple(Compressive_Harr_Feature& Harr_featue)
{

	// generator the input positive image 
	Mat Pos_image;Mat input_positive;
    Pos_image.create(Qustion_height,Question_width,CV_8UC1);
	for (int j=0;j<Pos_image.rows;j++)
	{
	    unsigned char *point =Pos_image.ptr<unsigned char>(j);
		for (int i=0;i<Pos_image.cols;i++)
		{
			*point=0;
			point++;     
		} 
	}

	//generator the neg image of input negtive
	Mat Neg_image;Mat input_negtive;
    Neg_image.create(Qustion_height,Question_width,CV_8UC1);
	for (int j=0;j<Neg_image.rows;j++)
	{
	    unsigned char *point =Neg_image.ptr<unsigned char>(j);
		for (int i=0;i<Neg_image.cols;i++)
		{
			*point=255;
			point++;     
		}
	}
	//generator the Pos and Neg feature vector of the neg and Pos image 
	resize(Pos_image,input_positive,Size(50,25),0,0,CV_INTER_NN);
	Harr_featue.Fill_pos_vector(input_positive,false);
	resize(Neg_image,input_negtive,Size(50,25),0,0,CV_INTER_NN);
	Harr_featue.Fill_neg_vector(input_negtive,false);
}

void DR_Question_Rect::Find_Question_with_Simlar_parament(int& index,Mat& Image_interst_ROI_Gray,Mat&Image_interst_ROI_Binary,Mat&Accluate_image_cpoy,Rect &set_off_rect,Compressive_Harr_Feature& Harr_featue)
{   
	Mat Whole_Gray;
	Whole_Gray.create(Image_Question_Location.rows,Image_Question_Location.cols,CV_8UC1);
	cvtColor(Image_Question_Location,Whole_Gray,CV_RGB2GRAY);
	vector<Point_SimlarParament>  More_Rect_points_Together;
	int Question_rect_had_find=0;
	for (int y=0;y<Accluate_image_cpoy.rows;y++)
	{   
		unsigned char * point =Accluate_image_cpoy.ptr<unsigned char >(y);
		for (int x=0;x<Accluate_image_cpoy.cols-Question_width;x++)
		{  
		   // here set two parets ,one is the pixs is zero ,other is 255
		   if(*point!=0)
		   {
			   point ++;
			   continue;
		   }
		   if (*point==0)
		   {
			   //
		      Question_rect_had_find++; // had find question rect is ++ own 
			  Point Temp_Location(x,y);
			  Rect_similar_information_get(Harr_featue,Accluate_image_cpoy,Whole_Gray,set_off_rect,Temp_Location,More_Rect_points_Together ,x,y);
			  
		   }
		
		}
	}
	//calculate the needing find points 

	int should_find_another_points=Question_number_information[index]-Question_rect_had_find;

	// here has the handle dirty ,it needs to find another two points 
	if (should_find_another_points<0)
	{
	   should_find_another_points=0;
	}
	if(should_find_another_points>=0)
	{
	  should_find_another_points+=1;
	}
	// Next step is find should_find_another_points in this circle search
	for(int addintion_index=0;addintion_index<should_find_another_points;addintion_index++)
	{  
	   double max_value=0;double min_value=0; Point min_loc(0,0);Point max_loc(0,0);
	   minMaxLoc(Accluate_image_cpoy,&min_value,&max_value,&min_loc,&max_loc);
	   Point Temp_Location(min_loc);
       Rect_similar_information_get(Harr_featue,Accluate_image_cpoy,Whole_Gray,set_off_rect,Temp_Location,More_Rect_points_Together ,min_loc.x,min_loc.y);
	
	}
	Fill_Rect_Locatin_by_SimlarParament(index,More_Rect_points_Together); 
	//Image_basic_function::Show_Image(Accluate_image_cpoy);
	
}

void DR_Question_Rect::Fill_Rect_Locatin_by_SimlarParament(int& index,vector<Point_SimlarParament> &More_Rect_points_Together)
{

	Doing_sort_by_Parament_Simlar(index ,More_Rect_points_Together);

	vector<Point>  Temp_candicate_Points;
	for(int j=0;j<Question_number_information[index]; j++)
	{
	
		Question_Location_information[index].push_back(More_Rect_points_Together[j].pt)	;
		Temp_candicate_Points.push_back(More_Rect_points_Together[j].pt);
	}

	//Here is need to delete out_line_points 
	Mat lin_message_index;
	Deep_check_with_RANSAC_To_Question_rect_by_hem_drity(lin_message_index,index);
	float inner_k=0;float inner_b=0;
	int inner_Points_Number=Get_model_by_Max_innernumber_Points(lin_message_index,inner_k,inner_b);
	
	// Delete the the Question_number_information[index] space 
	int delete_times=Question_Location_information[index].size();
	for (int times=0;times<delete_times;times++)
	{
	    Question_Location_information[index].erase(Question_Location_information[index].begin());     
	}

	// Re-- Fill the accomadate points to the detect Region 
	for (int down=0;down<Temp_candicate_Points.size();down++)
	{   
		float value=Temp_candicate_Points[down].y*inner_k+inner_b;
		if (abs(value-Temp_candicate_Points[down].x)<10.0)
		{   
		   Question_Location_information[index].push_back(Temp_candicate_Points[down]);
		}	
	}
}

void DR_Question_Rect::Doing_sort_by_Parament_Simlar(int&index ,vector<Point_SimlarParament> &More_Rect_points_Together)
{
	for (int i = 0; i<More_Rect_points_Together.size(); i++)
	{  
		Point_SimlarParament pt= More_Rect_points_Together[i];
		for (int j = More_Rect_points_Together.size() - 1; j>i; j--)
		{
			if (pt.simalar_Parament <= More_Rect_points_Together[j].simalar_Parament)
			{
				More_Rect_points_Together[i] = More_Rect_points_Together[j];
				More_Rect_points_Together[j] = pt;
				pt = More_Rect_points_Together[i];
			}
		}
	}  
}
void  DR_Question_Rect::Rect_similar_information_get(Compressive_Harr_Feature& Harr_featue,Mat &Accluate_image_cpoy,Mat &Whole_Gray,Rect& set_off_rect ,Point & Temp_Location,vector<Point_SimlarParament>&More_Rect_points_Together,int& x,int &y)
{       
	    //Fenerotor a bigger image basic the  set_off_rect 
	    Rect Bigger_New_set_off_rect (set_off_rect.x-Question_width,set_off_rect.y-Qustion_height,set_off_rect.width+2*Question_width,set_off_rect.height+2*Qustion_height);
		Mat  Bigger_New_set_off_Image,Bigger_New_set_off_Binary_Image;
		Bigger_New_set_off_Image.create(Bigger_New_set_off_rect.height,Bigger_New_set_off_rect.width,CV_8UC1);
		Bigger_New_set_off_Binary_Image.create(Bigger_New_set_off_rect.height,Bigger_New_set_off_rect.width,CV_8UC1);
		// Here is need to judge the crop rect image is overflow the edge

		if ((Bigger_New_set_off_rect.x+Bigger_New_set_off_rect.width)<=Whole_Gray.cols) 
		{
			if (Bigger_New_set_off_rect.x<0)
			{
				Image_basic_function::Set_Image_To_255_CV_8U(Bigger_New_set_off_Image);
				Rect Can_crop_Rect(0,Bigger_New_set_off_rect.y,Bigger_New_set_off_rect.width-abs(Bigger_New_set_off_rect.x),Bigger_New_set_off_rect.height);
				Mat Can_crop_Rect_Image;Can_crop_Rect_Image.create(Can_crop_Rect.height,Can_crop_Rect.width,CV_8UC1);
				Image_basic_function::Copy_Image(Whole_Gray,Can_crop_Rect_Image,Can_crop_Rect,true);
				Rect Project_Rect(abs(Bigger_New_set_off_rect.x),0,Bigger_New_set_off_rect.width-abs(Bigger_New_set_off_rect.x),Bigger_New_set_off_rect.height);
				Image_basic_function::Copy_Image(Can_crop_Rect_Image,Bigger_New_set_off_Image,Project_Rect,false);
			}
			else
			{
			   Image_basic_function::Copy_Image(Whole_Gray,Bigger_New_set_off_Image,Bigger_New_set_off_rect,true);
			}
		}
		else
		{   
			Image_basic_function::Set_Image_To_255_CV_8U(Bigger_New_set_off_Image);
			Rect Smaller_achieve_edge(Bigger_New_set_off_rect.x,Bigger_New_set_off_rect.y,Whole_Gray.cols-Bigger_New_set_off_rect.x-1,Bigger_New_set_off_rect.height);
			Mat  Smaller_achieve_edge_Image;
			Smaller_achieve_edge_Image.create(Smaller_achieve_edge.height,Smaller_achieve_edge.width,CV_8UC1);
			Image_basic_function::Copy_Image(Whole_Gray,Smaller_achieve_edge_Image,Smaller_achieve_edge,true);
			
			Rect Relative_Location(0,0,Smaller_achieve_edge.width,Smaller_achieve_edge.height);
			Image_basic_function::Copy_Image(Smaller_achieve_edge_Image,Bigger_New_set_off_Image,Relative_Location,false);
		}
		
		FastSauvolaBinarizer *point=new FastSauvolaBinarizer();
		point->Binary_way(Bigger_New_set_off_Image,Bigger_New_set_off_Binary_Image);
		delete point;
	    Rect Around_nigrboud((float)Temp_Location.x-(float)0.25*Question_width+(float)Question_width,(float)Temp_Location.y-(float)0.25*Qustion_height+(float)Qustion_height,2*Question_width,2*Qustion_height);
		Mat Temple_interst_Image(Around_nigrboud.height,Around_nigrboud.width,CV_8UC1);
		Image_basic_function::Copy_Image(Bigger_New_set_off_Binary_Image,Temple_interst_Image,Around_nigrboud,true);
		
		Temp_Location.x+=set_off_rect.x;
	    Temp_Location.y+=set_off_rect.y;
		Mat Binary_normal_image(25,50,CV_8UC1);
		resize(Temple_interst_Image,Binary_normal_image,Size(50,25),0,0,CV_INTER_NN);
	    vector<float> Haar_feature_candicate;
		Haar_feature_candicate=vector<float>((int)Harr_featue.Get__numFeature(), 0.0f);
		Harr_featue.Get_Harr_feture(Binary_normal_image,Haar_feature_candicate);
		float relationship_parament=Harr_featue.Similar_relationship(Haar_feature_candicate);
		//float relationship_parament1=Harr_featue.Similar_relationship_with_signle_Positive(Haar_feature_candicate);
		//cout<<relationship_parament<<"______"<<relationship_parament1<<endl;
		Point_SimlarParament temple(Temp_Location,relationship_parament);
		//Image_basic_function::Show_Image(Temple_interst_Image);
		More_Rect_points_Together.push_back(temple);
		Set_The_around_point_To_255(Accluate_image_cpoy,x,y);

}

void DR_Question_Rect::Find_Question_with_Zero_Min_points(int &index,Mat &Accluate_image_cpoy,Rect & set_off_rect,bool wheather_find_more_points)
{   
	int Question_rect_had_find=0;
	for (int y=0;y<Accluate_image_cpoy.rows;y++)
	{   
		unsigned char * point =Accluate_image_cpoy.ptr<unsigned char >(y);
		for (int x=0;x<Accluate_image_cpoy.cols-Question_width;x++)
		{  
		   // here set two parets ,one is the pixs is zero ,other is 255
		   if(*point!=0)
		   {
			   point ++;
			   continue;
		   }
		   if (*point==0)
		   {
		      Question_rect_had_find++; // had find question rect is ++ own 
			  Point Temp_Location(x,y);
			  Temp_Location.x+=set_off_rect.x;
			  Temp_Location.y+=set_off_rect.y;
			  Question_Location_information[index].push_back(Temp_Location);
			  //When get the Zero point ,the around zero point should be set to 255 
			  //so it will not be enter the Question_Location_information collect 
			  Set_The_around_point_To_255(Accluate_image_cpoy,x,y);
			
		   }
		
		}
	}
	//calculate the needing find points 
	int should_find_another_points=0;
	if (wheather_find_more_points==false)
	{
	  should_find_another_points=Question_number_information[index]-Question_rect_had_find;
	}

	if (wheather_find_more_points==true)// Here is used to find another Points in the ROI ,because it may have same Rect influence the judegement 
	{
	  should_find_another_points=Question_number_information[index]-Question_rect_had_find+1;
	}
	for(int addintion_index=0;addintion_index<should_find_another_points;addintion_index++)
	{  
	   double max_value=0;double min_value=0; Point min_loc(0,0);Point max_loc(0,0);
	   minMaxLoc(Accluate_image_cpoy,&min_value,&max_value,&min_loc,&max_loc);
	   Point Temp_Location(min_loc);
	   Temp_Location.x+=set_off_rect.x;
	   Temp_Location.y+=set_off_rect.y;
	   Question_Location_information[index].push_back(Temp_Location);
	   Set_The_around_point_To_255(Accluate_image_cpoy,min_loc.x,min_loc.y);

	}
}


void DR_Question_Rect::Find_Question_with_Zero_Min_points_Be_Mapping(int &index,Mat &Accluate_image_cpoy,Rect & set_off_rect,bool wheather_find_more_points)
{

	int Question_rect_had_find=0;
	for (int y=0;y<Accluate_image_cpoy.rows;y++)
	{   
		unsigned char * point =Accluate_image_cpoy.ptr<unsigned char >(y);
		for (int x=0;x<Accluate_image_cpoy.cols-Question_width;x++)
		{  
		   // here set two parets ,one is the pixs is zero ,other is 255
		   if(*point!=0)
		   {
			   point ++;
			   continue;
		   }
		   if (*point==0)
		   {
		      Question_rect_had_find++; // had find question rect is ++ own 
			  Point Temp_Location(x,y);
			  Temp_Location.x+=set_off_rect.x;
			  Temp_Location.y+=set_off_rect.y;
			  Question_Location_information[index].push_back(Temp_Location);
			  //When get the Zero point ,the around zero point should be set to 255 
			  //so it will not be enter the Question_Location_information collect 
			  Set_The_around_point_To_255(Accluate_image_cpoy,x,y);
			
		   }
		
		}
	}
	//calculate the needing find points 
	int should_find_another_points=0;
	if (wheather_find_more_points==false)
	{
	  should_find_another_points=Question_number_information[index]-Question_rect_had_find;
	}

	if (wheather_find_more_points==true)
	{
	  should_find_another_points=Question_number_information[index]-Question_rect_had_find+1;
	}
	for(int addintion_index=0;addintion_index<should_find_another_points;addintion_index++)
	{  
	   double max_value=0;double min_value=0; Point min_loc(0,0);Point max_loc(0,0);
	   minMaxLoc(Accluate_image_cpoy,&min_value,&max_value,&min_loc,&max_loc);
	   if (min_value>100)
	   {
		   break;
	   }
	   Point Temp_Location(min_loc);
	   Temp_Location.x+=set_off_rect.x;
	   Temp_Location.y+=set_off_rect.y;
	   Question_Location_information[index].push_back(Temp_Location);

	   Set_The_around_point_To_255(Accluate_image_cpoy,min_loc.x,min_loc.y);

	}
}

void DR_Question_Rect::Find_Question_with_Zero_Min_points_by_Position_limit(vector<vector<Point>> &Had_virtual_Question_Points,
	                                                                        int& index,Mat& Accluate_image_cpoy,Rect & set_off_rect,bool wheather_find_more_points)
{ 
	int Question_rect_had_find=0;
	for (int y=0;y<Accluate_image_cpoy.rows;y++)
	{   
		unsigned char * point =Accluate_image_cpoy.ptr<unsigned char >(y);
		for (int x=0;x<Accluate_image_cpoy.cols-Question_width;x++)
		{  
		   // here set two parets ,one is the pixs is zero ,other is 255
		   if(*point!=0)
		   {
			   point ++; 
			   continue;
		   }
		   if (*point==0)
		   {
		      //Intialize The find Real Points in Question Missing Image 
			  Point Temp_Location(x,y);
			  Temp_Location.x+=set_off_rect.x;
			  Temp_Location.y+=set_off_rect.y;

			  int correspoinding_Location_index=-1;
			  for(int index_find=0;index_find<Had_virtual_Question_Points[index].size();index_find++)
			  {
				  Point temple(Had_virtual_Question_Points[index][index_find].x,Had_virtual_Question_Points[index][index_find].y);
				  if (abs(Temp_Location.x-temple.x)<Question_width&&abs(Temp_Location.y-temple.y)<1.5*Qustion_height)
				  {
					  correspoinding_Location_index=index_find;
					  break;
				  }
			  }
			  if(correspoinding_Location_index==-1)
			  {  
				 Set_The_around_point_To_255(Accluate_image_cpoy,x,y);
			     continue;
			  }
			  if(correspoinding_Location_index!=-1)
			  {
				  Temp_Real_points[index][correspoinding_Location_index]=Temp_Location;
				  Question_rect_had_find++; // had find question rect is ++ own 
				  //When get the Zero point ,the around zero point should be set to 255 
				  //so it will not be enter the Question_Location_information collect 
				  Set_The_around_point_To_255(Accluate_image_cpoy,x,y);
			  }
		   }
		}
	}
	// Geneter the similar judgement to judge the left top Point whether corresponding to the Question Point 
	Compressive_Harr_Feature Harr_featue;
	Get_Pos_Neg_Vector_Sorce_Temple(Harr_featue);
	//calculate the needing find points 
	int should_find_another_points=0;
	if (wheather_find_more_points==false)
	{
	  should_find_another_points=Question_number_information[index]-Question_rect_had_find;
	}
	if (wheather_find_more_points==true)
	{
	  should_find_another_points=Question_number_information[index]-Question_rect_had_find+1;
	}
	for(int addintion_index=0;addintion_index<should_find_another_points;addintion_index++)
	{  
	   double max_value=0;double min_value=0; Point min_loc(0,0);Point max_loc(0,0);
	   minMaxLoc(Accluate_image_cpoy,&min_value,&max_value,&min_loc,&max_loc);
	   Point Temp_Location(min_loc);
	   Temp_Location.x+=set_off_rect.x;
	   Temp_Location.y+=set_off_rect.y;

	   int correspoinding_Location_index=-1;
	   for(int index_find=0;index_find<Had_virtual_Question_Points[index].size();index_find++)
	   {
			Point temple(Had_virtual_Question_Points[index][index_find].x,Had_virtual_Question_Points[index][index_find].y);
			if (abs(Temp_Location.x-temple.x)<Question_width&&abs(Temp_Location.y-temple.y)<1.5*Qustion_height)
			{   
				float Compressive_Harr_Cofficient=Get_The_judgement_cofficient_by_Harr(set_off_rect,min_loc,Harr_featue);
				if(Compressive_Harr_Cofficient>2000) 
				{
				   correspoinding_Location_index=index_find;
				   break;
				}
			}
	   }
	   if(correspoinding_Location_index==-1)
	   {    
		    Set_The_around_point_To_255(Accluate_image_cpoy,min_loc.x,min_loc.y);
			continue;
	   }
	   if(correspoinding_Location_index!=-1)
	   {

			Temp_Real_points[index][correspoinding_Location_index]=Temp_Location;
			Question_rect_had_find++; // had find question rect is ++ own 
			//When get the Zero point ,the around zero point should be set to 255 
			//so it will not be enter the Question_Location_information collect 
			Set_The_around_point_To_255(Accluate_image_cpoy,min_loc.x,min_loc.y);
	   }
	}
}

float   DR_Question_Rect::Get_The_judgement_cofficient_by_Harr(Rect& set_off_rect, Point& min_loc,Compressive_Harr_Feature &Harr_featue)
{     
	    Mat Whole_Gray;
		cvtColor(Image_Question_Location,Whole_Gray,CV_RGB2GRAY);	   
	   //Fenerotor a bigger image basic the  set_off_rect 
	    Rect Bigger_New_set_off_rect (set_off_rect.x-Question_width,set_off_rect.y-Qustion_height,set_off_rect.width+2*Question_width,set_off_rect.height+2*Qustion_height);
		Mat  Bigger_New_set_off_Image,Bigger_New_set_off_Binary_Image;
		Bigger_New_set_off_Image.create(Bigger_New_set_off_rect.height,Bigger_New_set_off_rect.width,CV_8UC1);
		Bigger_New_set_off_Binary_Image.create(Bigger_New_set_off_rect.height,Bigger_New_set_off_rect.width,CV_8UC1);
		// Crop the Image fo the input source gray
		if ((Bigger_New_set_off_rect.x+Bigger_New_set_off_rect.width)<=Whole_Gray.cols) 
		{
			if (Bigger_New_set_off_rect.x<0)
			{
				Image_basic_function::Set_Image_To_255_CV_8U(Bigger_New_set_off_Image);
				Rect Can_crop_Rect(0,Bigger_New_set_off_rect.y,Bigger_New_set_off_rect.width-abs(Bigger_New_set_off_rect.x),Bigger_New_set_off_rect.height);
				Mat Can_crop_Rect_Image;Can_crop_Rect_Image.create(Can_crop_Rect.height,Can_crop_Rect.width,CV_8UC1);
				Image_basic_function::Copy_Image(Whole_Gray,Can_crop_Rect_Image,Can_crop_Rect,true);
				Rect Project_Rect(abs(Bigger_New_set_off_rect.x),0,Bigger_New_set_off_rect.width-abs(Bigger_New_set_off_rect.x),Bigger_New_set_off_rect.height);
				Image_basic_function::Copy_Image(Can_crop_Rect_Image,Bigger_New_set_off_Image,Project_Rect,false);
			}
			else
			{
			   Image_basic_function::Copy_Image(Whole_Gray,Bigger_New_set_off_Image,Bigger_New_set_off_rect,true);
			}
		}
		else
		{   
			Image_basic_function::Set_Image_To_255_CV_8U(Bigger_New_set_off_Image);
			Rect Smaller_achieve_edge(Bigger_New_set_off_rect.x,Bigger_New_set_off_rect.y,Whole_Gray.cols-Bigger_New_set_off_rect.x-1,Bigger_New_set_off_rect.height);
			Mat  Smaller_achieve_edge_Image;
			Smaller_achieve_edge_Image.create(Smaller_achieve_edge.height,Smaller_achieve_edge.width,CV_8UC1);
			Image_basic_function::Copy_Image(Whole_Gray,Smaller_achieve_edge_Image,Smaller_achieve_edge,true);
			
			Rect Relative_Location(0,0,Smaller_achieve_edge.width,Smaller_achieve_edge.height);
			Image_basic_function::Copy_Image(Smaller_achieve_edge_Image,Bigger_New_set_off_Image,Relative_Location,false);
		}
		FastSauvolaBinarizer *point=new FastSauvolaBinarizer();
		point->Binary_way(Bigger_New_set_off_Image,Bigger_New_set_off_Binary_Image);
		delete point;

	    Rect Around_nigrboud((float)min_loc.x+(float)Question_width,(float)min_loc.y+(float)Qustion_height,Question_width,Qustion_height);
		Mat Temple_interst_Image(Around_nigrboud.height,Around_nigrboud.width,CV_8UC1);
		Image_basic_function::Copy_Image(Bigger_New_set_off_Binary_Image,Temple_interst_Image,Around_nigrboud,true);

		Mat Binary_normal_image(25,50,CV_8UC1);
		resize(Temple_interst_Image,Binary_normal_image,Size(50,25),0,0,CV_INTER_NN);
	    vector<float> Haar_feature_candicate;
		Haar_feature_candicate=vector<float>((int)Harr_featue.Get__numFeature(), 0.0f);
		Harr_featue.Get_Harr_feture(Binary_normal_image,Haar_feature_candicate);
		float relationship_parament=Harr_featue.Similar_relationship(Haar_feature_candicate);
		return relationship_parament;
}
void  DR_Question_Rect::Find_Question_with_Zero_Min_points_additional_by_model(int &index,Mat &Accluate_image_cpoy,Rect &set_off_rect,float &inner_k,float &inner_b)
{   
	int delete_times=Question_Location_information[index].size();
	for (int j=0;j<delete_times;j++)  //  erase the whole had detected Question Rect 
	{
		Question_Location_information[index].erase(Question_Location_information[index].begin());
	}
	int Question_rect_had_find=0;
	for (int y=0;y<Accluate_image_cpoy.rows;y++)
	{   
		unsigned char * point =Accluate_image_cpoy.ptr<unsigned char >(y);
		for (int x=0;x<Accluate_image_cpoy.cols-Question_width;x++)
		{  
		   // here set two parets ,one is the pixs is zero ,other is 255
		   if(*point!=0) 
		   {
			   point ++;
			   continue;
		   }
		   if (*point==0)
		   { 
			
			  Point Temp_Location(x,y);
			  Temp_Location.x+=set_off_rect.x;
			  Temp_Location.y+=set_off_rect.y;
			  float value=Temp_Location.y*inner_k+inner_b;
			  if (abs(value-Temp_Location.x)>5.0)
			  {   
				  point++;
			      Set_The_around_point_To_255(Accluate_image_cpoy,x,y); 
				  continue;
			  }
			  Question_rect_had_find++;
			  Question_Location_information[index].push_back(Temp_Location);
			  //When get the Zero point ,the around zero point should be set to 255 
			  //so it will not be enter the Question_Location_information collect 
			  Set_The_around_point_To_255(Accluate_image_cpoy,x,y);
			  point++;
		   }
		
		}
	  
	}

	//calculate the needing find points 
	int should_find_another_points=Question_number_information[index]-Question_rect_had_find;
	int fore_out_flag=0;
	for(int addintion_index=0;addintion_index<should_find_another_points;addintion_index++)
	{  
	   if(fore_out_flag>100)
	   {
	     break;
	   }
	   double max_value=0;double min_value=0; Point min_loc(0,0);Point max_loc(0,0);
	   minMaxLoc(Accluate_image_cpoy,&min_value,&max_value,&min_loc,&max_loc);
	   Point Temp_Location(min_loc);

	   if (abs(Temp_Location.y-Accluate_image_cpoy.rows)<20)
	   {
			addintion_index--;
			Set_The_around_point_To_255(Accluate_image_cpoy,Temp_Location.x,Temp_Location.y);
			continue;
	   }
	   Temp_Location.x+=set_off_rect.x;
	   Temp_Location.y+=set_off_rect.y;
	   float value_x=Temp_Location.y*inner_k+inner_b;
	   // Here is have a thousould in here ,so it is simlar can enter the candidate ,but from the test it occurs a bad case The wrong points doing set around to 255 
	   // influence the real points ,because the set action is near the Points rigions 
	   if (abs(value_x-Temp_Location.x)>6)
	   {
	        addintion_index--;
			int back_x=Temp_Location.x-set_off_rect.x;int back_y=Temp_Location.y-set_off_rect.y;
			Set_The_around_point_To_255(Accluate_image_cpoy,back_x,back_y);
			fore_out_flag++;
			continue;
	   
	   }
	   Question_Location_information[index].push_back(Temp_Location);
	   Set_The_around_point_To_255(Accluate_image_cpoy,min_loc.x,min_loc.y);
	}
}

void  DR_Question_Rect::Set_The_around_point_To_255(Mat &Accluate_image_cpoy,int & x,int & y)
{
	 for(int setoffy=y-Qustion_height;setoffy<y+2*Qustion_height;setoffy++)
	 { 
		if (setoffy<0)
		{
		  continue;
		}
	    unsigned char * point =Accluate_image_cpoy.ptr<unsigned char>(setoffy);
		int dx=x-Question_width;
		if (dx<=0)
		{
		    dx=0;
		}
		point+=dx;
		if (setoffy>Accluate_image_cpoy.rows-1)
		{
		   continue;
		}
		if (setoffy<0)
		{
		    continue;
		}
		for (int setoffx=x-Question_width;setoffx<x+2*Question_width;setoffx++)
		{
		      if (setoffx<0)
			  {
				 continue;
			  }
			  if(setoffx>Accluate_image_cpoy.cols)
			  {
			     continue;
			  }
			  * point=255;
			  point++;
		}
	 }
}

void DR_Question_Rect::Simple_check_with_RANSAC_To_Question_rect(int& index )
{   
	if (Question_Location_information[index].size()==1||Question_Location_information[index].size()==2) // when the question number is one or two the Ransaic is not use  
	{
	    exception_meaning =-1;
	}
     
	if(Question_Location_information[index].size()>2) //if the question rect points number is up to three ,the simple rect judegement is used 
	{
		  // initiozation is the frist ,here have the point (x1,y1) and (x2,y2)  
	      float x1=Question_Location_information[index][0].x; float  y1=Question_Location_information[index][0].y;
	      float x2=Question_Location_information[index][1].x; float  y2=Question_Location_information[index][1].y;
	      if (y2==y1)  // separate the case of  y1=y2
		  {
		     y2+=0.001;
          }
		  int whole_inner_number =2;
          float k=(x2-x1)/(y2-y1); //  in case the vertical ,so use the x=ky+b type 
		  float b=(x2*y1-x1*y2)/(y1-y2);

		  for ( int j=2;j<Question_Location_information[index].size();j++ )
		  {
		  
			 float value_x=Question_Location_information[index][j].y*k+b;
			 if ((abs(value_x-Question_Location_information[index][j].x))<5.0)
			 {
			    whole_inner_number++;
			 }
		  }

		  if (whole_inner_number==Question_Location_information[index] .size())
		  {
		     exception_meaning=-1;
		  
		  }
		  else
		  {
		     exception_meaning=2;
		  }
	}
}
void DR_Question_Rect::Deep_check_with_RANSAC_To_Question_rect(Mat & lin_message_index,int &index)
{
	int circle_nmuber=0;
	float inner_k=0; float inner_b=0; int inner_number=0;
	lin_message_index.create((Question_Location_information[index].size()-1)*Question_Location_information[index].size()/2,3,CV_32FC1);
	for(int up =0; up<Question_Location_information[index].size()-1;up++)  // Get the lageest inner number points 
    {	    
		for (int down=up+1; down<Question_Location_information[index].size();down++)
		{	
			float x1=Question_Location_information[index][up].x; float y1=Question_Location_information[index][up].y;
			float x2=Question_Location_information[index][down].x; float y2=Question_Location_information[index][down].y;
			if (y2==y1)
			{
			  y2+=0.001;
			}
			inner_k=(x2-x1)/(y2-y1);
			inner_b=(x2*y1-x1*y2)/(y1-y2);	
			for (int start =0;start<Question_Location_information[index].size();start++)
			{	     
				float value_x=Question_Location_information[index][start].y*inner_k+inner_b;
				if ((abs(value_x-Question_Location_information[index][start].x))<5.0)
				{
					inner_number++;
				}		
			}
			float * point = lin_message_index.ptr<float>(circle_nmuber);
			*point= inner_k;
			*(point+1)=inner_b;
			*(point+2)=inner_number;
			inner_number =0;
			circle_nmuber++;		   
		}	 
	}
}


void DR_Question_Rect::Deep_check_with_RANSAC_To_Question_rect_by_hem_drity(Mat & lin_message_index,int &index)
{
	int circle_nmuber=0;
	float inner_k=0; float inner_b=0; int inner_number=0;
	lin_message_index.create((Question_Location_information[index].size()-1)*Question_Location_information[index].size()/2,3,CV_32FC1);
	for(int up =0; up<Question_Location_information[index].size()-1;up++)  // Get the lageest inner number points 
    {	    
		for (int down=up+1; down<Question_Location_information[index].size();down++)
		{	
			float x1=Question_Location_information[index][up].x; float y1=Question_Location_information[index][up].y;
			float x2=Question_Location_information[index][down].x; float y2=Question_Location_information[index][down].y;
			if (y2==y1)
			{
			  y2+=0.001;
			}
			inner_k=(x2-x1)/(y2-y1);
			inner_b=(x2*y1-x1*y2)/(y1-y2);	
			for (int start =0;start<Question_Location_information[index].size();start++)
			{	     
				float value_x=Question_Location_information[index][start].y*inner_k+inner_b;
				if ((abs(value_x-Question_Location_information[index][start].x))<10.0)
				{
					inner_number++;
				}		
			}
			float * point = lin_message_index.ptr<float>(circle_nmuber);
			*point= inner_k;
			*(point+1)=inner_b;
			*(point+2)=inner_number;
			inner_number =0;
			circle_nmuber++;		   
		}	 
	}
}
void DR_Question_Rect::Deep_check_with_RANSAC_To_Question_rect_by_Limit_Condition(Mat&  lin_message_index,int&  index)
{
	int circle_nmuber=0;
	float inner_k=0; float inner_b=0; int inner_number=0;
	lin_message_index.create((Temp_Real_points[index].size()-1)*Temp_Real_points[index].size()/2,3,CV_32FC1);
	Image_basic_function::Set_Image_To_0_CV_32F(lin_message_index);
	for(int up =0; up<Temp_Real_points[index].size()-1;up++)  //Get the lageest inner number points 
    {	    
		for (int down=up+1; down<Temp_Real_points[index].size();down++)
		{	
			float x1=Temp_Real_points[index][up].x; float y1=Temp_Real_points[index][up].y;
			float x2=Temp_Real_points[index][down].x; float y2=Temp_Real_points[index][down].y;

			if(x1==0.||y1==0.||x2==0.||y2==0.)
			{   
				circle_nmuber++;
			    continue;
			}
			if (y2==y1)
			{
			  y2+=0.001;
			}
			inner_k=(x2-x1)/(y2-y1);
			inner_b=(x2*y1-x1*y2)/(y1-y2);	
			for (int start =0;start<Temp_Real_points[index].size();start++)
			{	     
				float value_x=Temp_Real_points[index][start].y*inner_k+inner_b;
				if ((abs(value_x-Temp_Real_points[index][start].x))<5.0)
				{
					inner_number++;
				}		
			}
			float * point = lin_message_index.ptr<float>(circle_nmuber);
			*point= inner_k;
			*(point+1)=inner_b;
			*(point+2)=inner_number;
			inner_number =0;
			circle_nmuber++;		   
		}	 
	}
}
void DR_Question_Rect::RANSAC_Alogrithem_To_Separarte_Out_Points(int& index )
{   
	// The function is to find the max number of inner points ,and the Question Points should achieve a limit lower stand 
	Mat lin_message_index;
	Deep_check_with_RANSAC_To_Question_rect_by_Limit_Condition(lin_message_index,index);

	float inner_k=0;float inner_b=0;
	Get_model_by_Max_innernumber(lin_message_index,inner_k,inner_b);
	Set_The_Out_points_To_Zero(index,inner_k,inner_b);
}

void DR_Question_Rect::Set_The_Out_points_To_Zero(int& index,float& inner_k,float& inner_b)
{
	for (int j=0;j<Temp_Real_points[index].size();j++)
	{
	    float value=Temp_Real_points[index][j].y*inner_k+inner_b;
		if (abs(value-Temp_Real_points[index][j].x)>5.0)
	    {   
			Point Out_Point_Initialize(0,0);
			Temp_Real_points[index][j]=Out_Point_Initialize;
		}
	}
}
void DR_Question_Rect::Get_model_by_Max_innernumber(Mat& lin_message_index,float& inner_k,float& inner_b)
{
	int max_inner_number=0;
	for (int a=0;a<lin_message_index.rows;a++)
	{
		float * point =lin_message_index.ptr<float>(a);
		for(int b=0;b<1;b++) // here just once ,because the width of the lin_message_index is 3 ,just once is Ok 
		{
			if (max_inner_number<*(point+2))
			{
				max_inner_number=*(point+2);
				inner_k=*(point); 
				inner_b=*(point+1); 	  
			}
				    
		 }
	}
}


int DR_Question_Rect::Get_model_by_Max_innernumber_Points(Mat& lin_message_index,float& inner_k,float& inner_b)
{

    int max_inner_number=0;
	for (int a=0;a<lin_message_index.rows;a++)
	{
		float * point =lin_message_index.ptr<float>(a);
		for(int b=0;b<1;b++) // here just once ,because the width of the lin_message_index is 3 ,just once is Ok 
		{
			if (max_inner_number<*(point+2))
			{
				max_inner_number=*(point+2);
				inner_k=*(point); 
				inner_b=*(point+1); 	  
			}
				    
		 }
	}
	return max_inner_number;
}

void DR_Question_Rect::Check_Question_rect_Location()
{ 
   // frist check is from the detected Question Rect number  
   if (exception_meaning==-1)
   {   
	   for(int j=0;j<Question_Location_information.size();j++)
	   {
	       if (Question_number_information[j]== Question_Location_information[j].size())
		   {
		         exception_meaning=-1;
		   }
		   else
		   {
			    exception_meaning=2;
				return ;
		   }
	   }
   }
   // doing a sort with the Question_number_information by the location of the points "Y" 
   Doing_sort_by_Y_Location();

   // check the Location of the correspond Location points of "Y" 

   if (exception_meaning==-1)
   {
	   for (int i=0;i< Question_number_information.size()/2;i++)
	   {   
			  if (i==0) 
			  {
				  i=0;
			  }
			  if (i==1)
			  {
				  i=2;
			  }

			  if (Question_number_information[i]!=0)
			  {
				  for (int down=0;down<Question_Location_information[i].size();down++)
				  {
					 int y1=Question_Location_information[i][down].y;
					 int y2=Question_Location_information[i+1][down].y;
					 if (abs(y1-y2)>12)
					 {
						exception_meaning=2;
						return ;

					 }
		      
				  }
			  }  
	   }
   }

}

void DR_Question_Rect::Check_Question_rect_Location_with_BOOL(bool& left ,bool& right)
{   
	// Reset the parament of the flag exception  ,here is false and it means that the imagenation the detect is right ,here is using false instead
	left=0;
	right=0;
	// frist check is from the detected Question Rect number  
	for(int j=0;j<Question_Location_information.size();j++)
	{   
		if (j==0||j==1)
		{
			if (Question_number_information[j]== Question_Location_information[j].size())
			{
				
			}
			else
			{
			    left=1;
				exception_meaning=2;
			}
		}
		if (j==2||j==3)
		{
			if (Question_number_information[j]== Question_Location_information[j].size())
			{
				
			}
			else
			{
			    right=1;
				exception_meaning=2;
			}
		   
		}
		  
	}
   // doing a sort with the Question_number_information by the location of the points "Y" 
   Doing_sort_by_Y_Location();

   // check the Location of the correspond Location points of "Y" 
  
	for (int i=0;i< (Question_number_information.size())/2;i++)
	{
		if (i==0) 
		{
			i=0;
		}
		if (i==1)
		{
			i=2;
		}
		// left check 

		if (Question_number_information[i]!=0)
		{
			if (i==0&&left==false)
			{
				for (int down=0;down<Question_Location_information[i].size();down++)
				{
					int y1=Question_Location_information[i][down].y;
					int y2=Question_Location_information[i+1][down].y;
					if (abs(y1-y2)>11)
					{
					exception_meaning=2;
					left=1;

					}
		      
				}
			}
			//  right check 
			if (i==2&&right==false)
			{
				for (int down=0;down<Question_Location_information[i].size();down++)
				{
					int y1=Question_Location_information[i][down].y;
					int y2=Question_Location_information[i+1][down].y;
					if (abs(y1-y2)>11)
					{
					exception_meaning=2;
					right=1;

					}
		      
				}
			}
		}
	}

	//  it needs to add a check to the Question_Location by the Y location 
	for (int i=0;i< (Question_number_information.size())/2;i++)
	{
		if (i==0) 
		{
			i=0;
		}
		if (i==1)
		{
			i=2;
		}

		if(Question_number_information[i]!=0)
		{
			// left check 
			if (i==0&&left==false)
			{
				for (int down=0;down<Question_Location_information[i].size()-1;down++)
				{   
					float x1=Question_Location_information[i][down].x;float y1=Question_Location_information[i][down].y;
					float x1_add=Question_Location_information[i][down+1].x;float y1_add=Question_Location_information[i][down+1].y;

					float x2=Question_Location_information[i+1][down].x;float y2=Question_Location_information[i+1][down].y;
					float x2_add=Question_Location_information[i+1][down+1].x;float y2_add=Question_Location_information[i+1][down+1].y;
					float distance_one=Image_basic_function::Distance_Between_Location( x1,y1,x1_add,y1_add);
					float distance_another=Image_basic_function::Distance_Between_Location( x2,y2,x2_add,y2_add);
					if (abs(distance_one-distance_another)>10)
					{
					  exception_meaning=2;
					  left=1;
					}
				}
			}

			//  right check 
			if (i==2&&right==false)
			{
				for (int down=0;down<Question_Location_information[i].size()-1;down++)
				{
					float x1=Question_Location_information[i][down].x;float y1=Question_Location_information[i][down].y;
					float x1_add=Question_Location_information[i][down+1].x;float y1_add=Question_Location_information[i][down+1].y;

					float x2=Question_Location_information[i+1][down].x;float y2=Question_Location_information[i+1][down].y;
					float x2_add=Question_Location_information[i+1][down+1].x;float y2_add=Question_Location_information[i+1][down+1].y;
					float distance_one=Image_basic_function::Distance_Between_Location( x1,y1,x1_add,y1_add);
					float distance_another=Image_basic_function::Distance_Between_Location( x2,y2,x2_add,y2_add);
					if (abs(distance_one-distance_another)>11)
					{
					  exception_meaning=2;
					  right=1;

					}
				}
			}
		}
	}
}

void DR_Question_Rect::Doing_sort_by_Y_Location()
{
	for (int k=0;k<Question_Location_information.size();k++)
	{
		for (int i = 0; i<Question_Location_information[k].size(); i++)
		{
                
			Point pt= Question_Location_information[k][i];
			for (int j = Question_Location_information[k].size() - 1; j>i; j--)
			{
				if (pt.y >= Question_Location_information[k][j].y)
				{
					Question_Location_information[k][i] = Question_Location_information[k][j];
					Question_Location_information[k][j] = pt;
					pt = Question_Location_information[k][i];
				}
			}
		}
    }
}

void DR_Question_Rect::Clear_relation_parament()
{
    exception_meaning=-1;
    for (int i=0;i<Question_Location_information.size();i++)
	{
	   int delete_times=Question_Location_information[i].size ();
	   for (int j=0;j<delete_times;j++)
	   {
		   Question_Location_information[i].erase(Question_Location_information[i].begin());            
	   }
	}
}

void DR_Question_Rect::Clear_Corresponding_Question_Locarion_Points(int& j)
{

	for (int index=j;index<j+2;index++)
	{
		int delete_times=Question_Location_information[index].size();
		for(int times=0;times<delete_times;times++)
		{
			Question_Location_information[index].erase(Question_Location_information[index].begin());
		}
	   
	}
 
}
void DR_Question_Rect::Set_The_aangle_start_And_angle_end(int& index,int & angle_start,int &angle_end)
{

	if (index==0) //A3 and A4 ---correspond left 
	{
	   angle_start=90.0;
	   angle_end=180.0 ;
	}

	
	if (index==1) //A4--- correspond right 
	{
	   angle_start=0.0;
	   angle_end=90.0 ;
	}

	if (index==2)//NONE use 
	{
	   angle_start=0.0;
	   angle_end=180.0 ;
	}

	if (index==3) // A3 ---correspond right 
	{
	   angle_start=0.0;
	   angle_end=90.0 ;
	}
}

void DR_Question_Rect::Find_line(Point &pt1,Point& pt2,Point& pt3 ,Point& pt4, Mat &The_Rho_space,int &rhomax,Mat&Image_interst_ROI)
{
	struct rhothe
	{
		float the;
		float rho;
	};
	rhothe Two_Parallel_lines[2];
	Two_Parallel_lines[0].the=0;
	Two_Parallel_lines[0].rho=0;
	Two_Parallel_lines[1].the=0;
	Two_Parallel_lines[1].rho=0;

	//Seek  the frist length line 
	for (int i=0;i<6;i++)
	{
		rhothe  templeline;
		double  MinValue;
		double  MaxValue; 
		Point MinLocation;
		Point MaxLocation;
		minMaxLoc(The_Rho_space,& MinValue,& MaxValue,& MinLocation,& MaxLocation);
		templeline.the=MaxLocation.x;
		templeline.rho=MaxLocation.y;
		templeline.rho=2*templeline.rho-rhomax;  	
		double a = cos(float(templeline.the*CV_PI/180)), b = sin(float(templeline.the*CV_PI/180));
		double x0 = a*templeline.rho, y0 = b*templeline.rho;
		pt1.x = cvRound(x0 + 5000*(-b));
		pt1.y = cvRound(y0 + 5000*(a));
		pt2.x = cvRound(x0 - 5000*(-b));
		pt2.y = cvRound(y0 - 5000*(a));
		if (templeline.rho>100)
		{
				Two_Parallel_lines[0]=templeline;
				Set_Point_Round_To_Zero(The_Rho_space,MaxLocation);
				break;
		}	
		Set_Point_Round_To_Zero(The_Rho_space,MaxLocation);
	 }
	// Seek the Second length  line 
	 for (int i=0;i<5;i++)
	 {
		rhothe  templeline;
		double  MinValue;
		double  MaxValue; 
		Point MinLocation;
		Point MaxLocation;
		minMaxLoc(The_Rho_space,& MinValue,& MaxValue,& MinLocation,& MaxLocation);
		templeline.the=MaxLocation.x;
		templeline.rho=MaxLocation.y;
		templeline.rho=2*templeline.rho-rhomax;  	
		double a = cos(float(templeline.the*CV_PI/180)), b = sin(float(templeline.the*CV_PI/180));
		double x0 = a*templeline.rho, y0 = b*templeline.rho;
		pt1.x = cvRound(x0 + 5000*(-b));
		pt1.y = cvRound(y0 + 5000*(a));
		pt2.x = cvRound(x0 - 5000*(-b));
		pt2.y = cvRound(y0 - 5000*(a));  
		int dif_the=abs(Two_Parallel_lines[0].the-templeline.the);
		int dif_rho=abs(Two_Parallel_lines[0].rho-Two_Parallel_lines[0].rho);
		if (dif_the<4.0&&dif_rho<40.0&&templeline.rho>100)
		{
			Two_Parallel_lines[1]=templeline;
			break;
		}
		Set_Point_Round_To_Zero(The_Rho_space,MaxLocation);
      }

	  //fill the point pt1 pt2 
	  rhothe up_line;
	  up_line=Two_Parallel_lines[0];
	  if (up_line.rho>Two_Parallel_lines[1].rho)
	  {
	    up_line=Two_Parallel_lines[1];
	  }
	  double a = cos(float(up_line.the*CV_PI/180)), b = sin(float(up_line.the*CV_PI/180));
	  double x0 = a*up_line.rho, y0 = b*up_line.rho;
	  pt1.x = cvRound(x0 + 5000*(-b));
	  pt1.y = cvRound(y0 + 5000*(a));
	  pt2.x = cvRound(x0 - 5000*(-b));
	  pt2.y = cvRound(y0 - 5000*(a)); 
	  
	  //fill the point  pt3 pt4 
	  up_line=Two_Parallel_lines[0];
	  if (up_line.rho<Two_Parallel_lines[1].rho)
	  {
	    up_line=Two_Parallel_lines[1];
	  }
	  a = cos(float(up_line.the*CV_PI/180));b = sin(float(up_line.the*CV_PI/180));
	  x0 = a*up_line.rho; y0 = b*up_line.rho;
	  pt3.x = cvRound(x0 + 5000*(-b));
	  pt3.y = cvRound(y0 + 5000*(a));
	  pt4.x = cvRound(x0 - 5000*(-b));
	  pt4.y = cvRound(y0 - 5000*(a)); 
}
void DR_Question_Rect::Set_Point_Round_To_Zero(Mat &The_Rho_space,Point& MaxLocation)
{
	int  x=MaxLocation.x;
	int  y=MaxLocation.y;
	int a =5;
	int b =5;
	for (int setoffy=y-(2*b);setoffy<y+(2*b);setoffy++)
	{   

		float * r=The_Rho_space.ptr<float>(setoffy);
		int dx=x-2*a;
		if (dx<0||dx==0)
		{
			dx=0;
		}
		r+=dx; //here make a big mistake  ,if the dx=0 we should  do nothing  ,just make the point add zero 

    	for (int setoffx=x-(2*a);setoffx<x+(2*a);setoffx++)
		{  
			if (setoffx<0)
			    continue;
			if (setoffy>The_Rho_space.rows)
				continue;
			if (setoffx>The_Rho_space.cols)
				continue;
			if (setoffy<0)
				continue;
			*r=0;
			 r++;
		}
	}
}
void DR_Question_Rect::Reverse_Pixs_With_Line(Mat& interest_ROI_binary,Point& pt1,Point&pt2,Point&pt3,Point& pt4)
{
	float k1=(float)(pt2.y-pt1.y)/(float)(pt2.x-pt1.x);
	float b1=(float)(pt2.y*pt1.x-pt1.y*pt2.x)/(float)(pt1.x-pt2.x); 
	float k2=(float)(pt4.y-pt3.y)/(float)(pt4.x-pt3.x);
	float b2=(float)(pt4.y*pt3.x-pt3.y*pt4.x)/(float)(pt3.x-pt4.x); 

	for(int j=0;j<interest_ROI_binary.rows;j++)
	{
		unsigned char* point = interest_ROI_binary.ptr<unsigned char>(j);
		for (int i=0;i<interest_ROI_binary.cols;i++)
		{
				  
			if ((k1*i+b1-j)<=0||(k2*i+b2-j)<=0)
			{
				* point=255;
			}
			point++;		 
		}
	}
}
void DR_Question_Rect::Mapping_Methord_To_Find_Qusetion_Rect(int& Map_index,int& Be_Map_index,Mat& Map_image,Mat& Be_Map_Image,Rect& Map_Rect_set_off,Rect& Be_Map_Rect_set_off,bool & Is_Matching)
{    
	//Image_basic_function::Show_Image(Map_image);
	Seek_The_best_Location(Map_index,Map_Rect_set_off,Map_image);
	Seek_Question_rect_Location_With_Be_Maping_Image(Be_Map_index,Be_Map_Image,Be_Map_Rect_set_off);
	Mapping_Corresponding_Search(Map_index,Be_Map_index);
	Making_check_With_The_Corresponding_Points(Map_index,Be_Map_index,Is_Matching);

}

void DR_Question_Rect::Seek_Question_rect_Location_With_Be_Maping_Image(int& Be_Map_index,Mat & Be_Map_Image,Rect& Be_Map_Rect_set_off)
{
	Mat  Accluate_image_cpoy;
	Accluate_image_cpoy=Be_Map_Image.clone();// making a copy of the Acculate_Box_image_based_Question_WH 
                                                       //because it may find wronging in the frist search
    Find_Question_with_Zero_Min_points_Be_Mapping(Be_Map_index,Accluate_image_cpoy,Be_Map_Rect_set_off,true); 

	if(Question_Location_information[Be_Map_index].size()<=3)
	{
	   return;
	}
	if (Question_Location_information[Be_Map_index].size()>3)// it present the simple Ransaic  OR detected Question number may be wrong at least on leaf 
	{   
	    Mat lin_message_index,Accluate_image_cpoy_Two;
		Accluate_image_cpoy_Two=Be_Map_Image.clone();
		Deep_check_with_RANSAC_To_Question_rect(lin_message_index,Be_Map_index);
		float inner_k=0;float inner_b=0;
		Get_model_by_Max_innernumber(lin_message_index,inner_k,inner_b);
		Using_model_To_delete_Points(Be_Map_index,inner_k,inner_b); 	
	}
 
}
void DR_Question_Rect::Using_model_To_delete_Points(int& Be_Map_index ,float& inner_k,float& inner_b)
{
	vector<Point> Temple_Points_Whole;
	for (int j=0;j<Question_Location_information[Be_Map_index].size();j++)
	{
		Temple_Points_Whole.push_back(Question_Location_information[Be_Map_index][j]);
	}
    int delete_times=Question_Location_information[Be_Map_index].size();
	for (int j=0;j<delete_times;j++)
	{
		Question_Location_information[Be_Map_index].erase(Question_Location_information[Be_Map_index].begin());
	}

	for (int j=0;j<Temple_Points_Whole.size();j++)
	{
		Point pt(Temple_Points_Whole[j]);
		float value_x=pt.y*inner_k+inner_b;
		if (abs(value_x-pt.x)<5)
		{
			Question_Location_information[Be_Map_index].push_back(pt);
		}
	}
}

void DR_Question_Rect::Mapping_Corresponding_Search(int& Map_index,int& Be_Map_index)
{
	vector<Point> Temple_Points_Whole;
	for (int j=0;j<Question_Location_information[Be_Map_index].size();j++)
	{
		Temple_Points_Whole.push_back(Question_Location_information[Be_Map_index][j]);
	}
    int delete_times=Question_Location_information[Be_Map_index].size();
	for (int j=0;j<delete_times;j++)
	{
		Question_Location_information[Be_Map_index].erase(Question_Location_information[Be_Map_index].begin());
	}

	for (int canditate_times=0;canditate_times<Temple_Points_Whole.size();canditate_times++)
	{   
		int canditate_Y_Location=Temple_Points_Whole[canditate_times].y;
	    for (int temple_times=0;temple_times<Question_Location_information[Map_index].size();temple_times++)
		{
			int temple_Y_Location=Question_Location_information[Map_index][temple_times].y;
			if (abs(canditate_Y_Location-temple_Y_Location)<5)
			{
				Question_Location_information[Be_Map_index].push_back(Temple_Points_Whole[canditate_times]);
			}
		}
	 }
}
void DR_Question_Rect::Making_check_With_The_Corresponding_Points(int& Map_index,int& Be_Map_index,bool& Is_Matching)
{
    if (Question_Location_information[Map_index].size()!=Question_Location_information[Be_Map_index].size())
	{
	    Is_Matching=false;
		return ;
	}
	if (Question_Location_information[Map_index].size()==Question_Location_information[Be_Map_index].size())
	{
	  Doing_sort_by_Y_Location_Not_Whole(Map_index);
	  Doing_sort_by_Y_Location_Not_Whole(Be_Map_index);
	  for (int i=0;i<Question_Location_information[Map_index].size();i++)
	  {
		  if(abs(Question_Location_information[Map_index][i].y-Question_Location_information[Be_Map_index][i].y)>5)
		  {
		    Is_Matching=false;
			return;
		  }

	  }
	}
}

void DR_Question_Rect::Doing_sort_by_Y_Location_Not_Whole(int &k)
{
	for (int i = 0; i<Question_Location_information[k].size(); i++)
	{       
		Point pt= Question_Location_information[k][i];
		for (int j = Question_Location_information[k].size() - 1; j>i; j--)
		{
			if (pt.y >= Question_Location_information[k][j].y)
			{
				Question_Location_information[k][i] = Question_Location_information[k][j];
				Question_Location_information[k][j] = pt;
				pt = Question_Location_information[k][i];
			}
		}
	}
}

void DR_Question_Rect::Save_The_Normal_detected_Rect_points(bool& left,bool& right)
{   
	Temp_Real_points=vector<vector<Point>>(Question_number_information.size(), vector<Point>());

	if (left==0)
	{  for (int i=0;i<DR_Question_Rect::Top_rect_Location_information.size()/2;i++)
	   {
		   for (int j=0;j<DR_Question_Rect::Question_Location_information[i].size();j++)
		   {
			   Temp_Real_points[i].push_back(Question_Location_information[i][j]);
		   }
	
	   }
	} 
	 
	if (right==0)
	{
	   for (int i=2;i<DR_Question_Rect::Top_rect_Location_information.size();i++)
	   {
		   for (int j=0;j<DR_Question_Rect::Question_Location_information[i].size();j++)
		   {
			   Temp_Real_points[i].push_back(Question_Location_information[i][j]);
		   }
	
	   }
	
	}
}

void DR_Question_Rect::Get_The_Have_save_Points(int& j)
{
	if (j==0)
	{  
	   for (int index=0;index<2;index++)
	   {   
		   for (int down=0;down<Temp_Real_points[index].size();down++)
		   {
			   Question_Location_information[index].push_back(Temp_Real_points[index][down]);
		   }
	   }
	
	}

	if (j==2)
	{
	   for (int index=2;index<4;index++)
	   {   
		   for (int down=0;down<Temp_Real_points[index].size();down++)
		   {
			   Question_Location_information[index].push_back(Temp_Real_points[index][down]);
		   }
	   }

	}
  
}
DR_Question_Rect::~DR_Question_Rect()
{


}