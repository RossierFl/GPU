#ifndef HEATTRANSFERT_H_
#define HEATTRANSFERT_H_

#include "cudaTools.h"
#include "Animable_I.h"
#include "MathTools.h"
#include "VariateurF.h"
#include "CalibreurCudas.h"

class HeatTransfert: public Animable_I {

	public:

		HeatTransfert(int w, int h, float k);
		virtual ~HeatTransfert();

		/**
		 * Override
		 * Call periodicly by the API
		 */
		virtual void animationStep();

		virtual void runGPU(uchar4* ptrDevPixels); // Override

		/*
		 * Animation parameters
		 */
		virtual float getT(); // Override
		virtual int getW(); // Override
		virtual int getH(); // Override
		virtual string getTitle(); // Override

	private:

		// Inputs
		int w;
		int h;
		float k;

		// Tools
		dim3 dg;
		dim3 db;
		CalibreurCudas calibreurCuda;

		float* ptrDevImageInit;
		float* ptrDevImageHeater;
		float* ptrDevImageA;
		float* ptrDevImageB;

		//Outputs
		string title;
};

#endif

