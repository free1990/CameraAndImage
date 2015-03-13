
#include "Fill_Missing_Question_Rect.h"

Fill_Missing_Question_Rect::Fill_Missing_Question_Rect():scale_width(0.370),scale_height(0.534),exception_meaning(-1)
{
		
}

void Fill_Missing_Question_Rect::Fill_The_Missing_Rect_by_Match_Model(Mat& Question_Rect_Missing_Image,vector<Fill_Missing_Question_Rect_Modle_Parament>& Stand_Model,
	                                                                           vector<Rect>& Top_Location_rect, vector<int>&Top_rect_information,vector<int>& Question_rect_information,int&exception_mean)
{   
	// The basic information of input arguemnt
	InitiaLize_basic_information(Top_Location_rect,Top_rect_information,Question_rect_information);

	// model parament for input arguemnt 
	InitiaLize_parament_model(Question_Rect_Missing_Image,Stand_Model);

	// Just by the liner relationship with to cross circles 
	Find_The_Missing_Point_by_linner_Line_With_Two_circle();

	// The finding points should be fixed ,because the virtual points is not correct ,it needing to be fixed by the stand length by dx and dy 
	Fix_Virtual_Points_by_Real_Question_Points();
}

void Fill_Missing_Question_Rect::InitiaLize_basic_information( vector<Rect>& Top_Location_rect,vector<int>&Top_rect_information,vector<int>& Question_rect_information)
{   
	// initialize the  information of uniform style 
	for (int i=0;i<Top_Location_rect.size();i++)
	{
		Top_rect_Location_information.push_back(Top_Location_rect[i]);
	}
	for (int i=0;i<Top_rect_information.size();i++)
	{
		Top_rect_number_information.push_back(Top_rect_information[i]);
	}
	for(int i=0;i<Question_rect_information.size();i++)
	{
		Question_number_information.push_back(Question_rect_information[i]);
	}

	// fill the current length of the input image  
	for (int j=0;j<Top_Location_rect.size();j++)
	{
		if(j%2==0)
		{   
			Point pt1(Top_Location_rect[j].x,Top_Location_rect[j].y);
			Point pt2(Top_Location_rect[j+1].x,Top_Location_rect[j+1].y);
			float distance_A3_Or_A4=Image_basic_function::Distance_Between_Points(pt1,pt2);
			// 
			Current_Length.push_back(distance_A3_Or_A4);
		}
		if(j%2!=0)
		{
			Point pt1(Top_Location_rect[j].x,Top_Location_rect[j].y);
			Point pt2(Top_Location_rect[j-1].x,Top_Location_rect[j-1].y);
			float distance_A3_Or_A4=Image_basic_function::Distance_Between_Points(pt1,pt2);
			Current_Length.push_back(distance_A3_Or_A4);
		}
	}

	// Question_Location_information space malloc 
	Question_Location_information=vector<vector<Point>>(Question_rect_information.size(),vector<Point>());

	// Question width and height to fill 
	float Whole_Width=0;float Whole_Height=0;
	for(int i=0;i<Top_rect_Location_information.size();i++)
	{
		Whole_Width+=Top_rect_Location_information[i].width;
		Whole_Height+=Top_rect_Location_information[i].height;
	}
	Question_width=scale_width*Whole_Width/Top_rect_Location_information.size();
	Qustion_height=scale_height*Whole_Height/Top_rect_Location_information.size();
}
void Fill_Missing_Question_Rect::InitiaLize_parament_model(Mat& Question_Rect_Missing_Image,vector<Fill_Missing_Question_Rect_Modle_Parament>& Stand_Model)
{   
	//Deep clone the image fo the canditate image for find The minssing Quretion Rect image
	Image_Question_Location=Question_Rect_Missing_Image.clone();

	// Fill the model information with model length_Top_Rect ¡¢Width_Top_Rect ¡¢Height_Top_Rect
	Template_Length=vector<vector<float>>(Stand_Model.size(),vector<float>());
	float distance_A3_Or_A4=0;float distance_A3_Right=0; float Top_Rect_Width_Whole=0;float Top_Rect_Height_Whole=0;
	for(int index=0;index<Stand_Model.size();index++)
	{   
		// First step is to calculate the distance of the top rect 
		for(int j=0;j<Stand_Model[index].Modle_Parament_with_Top_Rect.size();j++)
		{
		   if(j%2==0)
		   {   
			   Point pt1(Stand_Model[index].Modle_Parament_with_Top_Rect[j].x,Stand_Model[index].Modle_Parament_with_Top_Rect[j].y);
			   Point pt2(Stand_Model[index].Modle_Parament_with_Top_Rect[j+1].x,Stand_Model[index].Modle_Parament_with_Top_Rect[j+1].y);
			   distance_A3_Or_A4=Image_basic_function::Distance_Between_Points(pt1,pt2);
			   Template_Length[index].push_back(distance_A3_Or_A4);

		   }
		   if(j%2!=0)
		   {
		       Point pt1(Stand_Model[index].Modle_Parament_with_Top_Rect[j].x,Stand_Model[index].Modle_Parament_with_Top_Rect[j].y);
			   Point pt2(Stand_Model[index].Modle_Parament_with_Top_Rect[j-1].x,Stand_Model[index].Modle_Parament_with_Top_Rect[j-1].y);
			   distance_A3_Right=Image_basic_function::Distance_Between_Points(pt1,pt2);
			   Template_Length[index].push_back(distance_A3_Right);
		   }
		}
	}

	// Fill the scale relationship between the top rect and Question Rect
	Length_Scale_Left=vector<vector<vector<float>>>(Stand_Model.size(),vector<vector<float>>(Top_rect_Location_information.size(),vector<float>()));
	Length_Scale_Right=vector<vector<vector<float>>>(Stand_Model.size(),vector<vector<float>>(Top_rect_Location_information.size(),vector<float>()));
	for (int index=0;index<Stand_Model.size();index++)
	{
		for (int j=0;j<Stand_Model[index].Modle_Parament_with_Question_Rect.size();j++)
		{   
			float Temple_length=Template_Length[index][j];
			Point Tmple_pt_Left(0,0);Point Temp_pt_Right(0,0);
			if(j%2==0)
			{
				Point Pt_Left(Stand_Model[index].Modle_Parament_with_Top_Rect[j].x,Stand_Model[index].Modle_Parament_with_Top_Rect[j].y);
				Point pt_Right(Stand_Model[index].Modle_Parament_with_Top_Rect[j+1].x,Stand_Model[index].Modle_Parament_with_Top_Rect[j+1].y);
				Tmple_pt_Left=Pt_Left;
				Temp_pt_Right=pt_Right;
			}
		    if(j%2!=0)
			{
			    Point Pt_Left(Stand_Model[index].Modle_Parament_with_Top_Rect[j-1].x,Stand_Model[index].Modle_Parament_with_Top_Rect[j-1].y);
				Point pt_Right(Stand_Model[index].Modle_Parament_with_Top_Rect[j].x,Stand_Model[index].Modle_Parament_with_Top_Rect[j].y);
				Tmple_pt_Left=Pt_Left;
				Temp_pt_Right=pt_Right;
			}
			for (int down=0;down<Stand_Model[index].Modle_Parament_with_Question_Rect[j].size();down++)
			{
				Point Candicate_Point(Stand_Model[index].Modle_Parament_with_Question_Rect[j][down].x,Stand_Model[index].Modle_Parament_with_Question_Rect[j][down].y);
				float distance_left=Image_basic_function::Distance_Between_Points(Tmple_pt_Left,Candicate_Point);
				float distance_right=Image_basic_function::Distance_Between_Points(Temp_pt_Right,Candicate_Point);
				float scale_left=distance_left/Temple_length; float scale_right=distance_right/Temple_length;
				Length_Scale_Left[index][j].push_back(scale_left);
				Length_Scale_Right[index][j].push_back(scale_right);	   
			}		   
		}
	}
}

void Fill_Missing_Question_Rect::Find_The_Missing_Point_by_linner_Line_With_Two_circle()
{   
	// fill The temple length scale of the temple stand 
	vector <vector<float>> Length_Scale_Left_average;
	vector <vector<float>> Length_Scale_Right_average;
	Length_Scale_Left_average=vector<vector<float>>(Top_rect_Location_information.size(),vector<float>());
	Length_Scale_Right_average=vector<vector<float>>(Top_rect_Location_information.size(),vector<float>());
	for(int i=0;i<Length_Scale_Left_average.size();i++)
	{ 
	   for (int times=0;times<Question_number_information[i];times++)
	   {    
	       float scale_left_Whole=0; float scale_right_Whole=0;
		   for (int index=0;index<Length_Scale_Left.size();index++)
		   {   
			 scale_left_Whole+=Length_Scale_Left[index][i][times];
			 scale_right_Whole+=Length_Scale_Right[index][i][times];
		   }
		   scale_left_Whole=scale_left_Whole/Length_Scale_Left.size();
		   scale_right_Whole=scale_right_Whole/Length_Scale_Left.size();
		   Length_Scale_Left_average[i].push_back(scale_left_Whole);
		   Length_Scale_Right_average[i].push_back(scale_right_Whole);
	   }
    }

	// find the missing points 
	for (int j=0;j<Question_Location_information.size();j++)
	{   
		Point left_point(0,0);Point right_point(0,0); 
		if(j%2==0)
		{
			Point Pt_Left(Top_rect_Location_information[j].x,Top_rect_Location_information[j].y);
			Point pt_Right(Top_rect_Location_information[j+1].x,Top_rect_Location_information[j+1].y);
			left_point=Pt_Left;
			right_point=pt_Right;
		}
		if(j%2!=0)
		{
			Point Pt_Left(Top_rect_Location_information[j-1].x,Top_rect_Location_information[j-1].y);
			Point pt_Right(Top_rect_Location_information[j].x,Top_rect_Location_information[j].y);
			left_point=Pt_Left;
			right_point=pt_Right;
		}
		for(int index=0;index<Length_Scale_Left_average[j].size();index++)
		{
			float left_length_single=Current_Length[j]*Length_Scale_Left_average[j][index];
			float right_length_single=Current_Length[j]*Length_Scale_Right_average[j][index];
			float x1=0,y1=0,x2=0,y2=0;
			int bool_flage=Image_basic_function::circle_circle_intersection(left_point.x,left_point.y,left_length_single,right_point.x,right_point.y,right_length_single,&x1,&y1,&x2,&y2);
			if (bool_flage==1)
			{    
				if (y1>=y2)
				{
					 Point vritual_point(x1,y1);
					 Question_Location_information[j].push_back(vritual_point);
				
				}
				else
				{
				     Point vritual_point(x2,y2);
					 Question_Location_information[j].push_back(vritual_point);
				}
			}
		}
	}
}	

void Fill_Missing_Question_Rect::Fix_Virtual_Points_by_Real_Question_Points()
{   
	DR_Question_Rect *point=new DR_Question_Rect();
 	point->Missing_Rect_Points_fixed(Image_Question_Location,Question_Location_information,Top_rect_Location_information,Top_rect_number_information,Question_number_information,exception_meaning);
	delete point;
}

Fill_Missing_Question_Rect::~Fill_Missing_Question_Rect()
{

}