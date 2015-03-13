#pragma once
#include <opencv2/opencv.hpp>
#include "iostream"
using namespace cv;

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "Exam_Paper_Analysis.h"
#include "FastSauvolaBinarizer.h"



	struct Thoushould_Location
	{
	   float Thoushould;
	   int Question_number;
	   int Question_Choice;
	};




class Choice_Question_Recognize
{
public:
	Choice_Question_Recognize();
	~Choice_Question_Recognize();
public:
	void Judge_Choice_Option(Mat& Input ,vector<Rect> Rect_List ,Vector<bool> Result_Chioce);
public:
	void Judgement_Nessary(Exam_Paper_Analysis *& ponit);

public:

	void Choice_Question_Algotrthm(Exam_Paper_Analysis *& ponit);


	void  Red_Points_analysis(Exam_Paper_Analysis *& ponit);
private:
	void Judgement_Frist_Low_Thousould (Exam_Paper_Analysis *& ponit,vector<vector<bool>>&  Question_Choice_index_Together_Frist_Low);

	void Judgement_Frist_Low_Thousould_Second (Exam_Paper_Analysis *& ponit,vector<vector<bool>>&  Question_Choice_index_Together_Frist_Low);

	void Filling_Corresponding_Location_Frist(vector<vector<bool>> &Question_Choice_index_Together_Frist_Low,
	                                                                  Exam_Paper_Analysis *&ponit,
																	  vector<vector<float>>& Up_Togrther,
																	  vector<vector<float>>& Down_Together,
																	  vector<vector<float>>& Static_Black_Points);

   void Filling_Corresponding_Location_Second(vector<vector<bool>> &Question_Choice_index_Together_Frist_Low,
	                                                                  Exam_Paper_Analysis *&ponit,
																	  vector<vector<float>>& Up_Togrther,
																	  vector<vector<float>>& Down_Together,
																	  vector<vector<float>>& Static_Black_Points);

   void Judgement_with_Prior_Knowledge(vector<vector<bool>> & Question_Choice_index_Together_Frist_Low,
	                                    vector<vector<float>>& Static_Black_Points,
										vector<vector<float>>& Up_Togrther,
										vector<vector<float>>& Down_Together);

   
  void Get_The_UP_List( vector<vector<float>>&  Up_Togrther,vector<Thoushould_Location> &Up_Thoushould_List);

  void Get_The_Down_List(vector<vector<float>>&Down_Together, vector<Thoushould_Location> & Down_Thoushould_List);

  void Show_The_Result_Of_Last_Decision_UP(Exam_Paper_Analysis *& ponit,vector<vector<bool>> & Last_decision_Choice);
  void Show_The_Result_Of_Last_Decision_DOWN(Exam_Paper_Analysis *& ponit,vector<vector<bool>> & Last_decision_Choice);
};