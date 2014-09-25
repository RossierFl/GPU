#ifndef SCENARIOMANAGER_H_
#define SCENARIOMANAGER_H_
#include "envCanvasJNI.h"
#include "Scenario.h"

#include <map>
using std::map;

#include <mutex>
//#include <boost/thread/mutex.hpp>
using std::mutex;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

// Probleme:
  // 	 	La destruction de l'objet Scenario
  //
  // Solution:
  // 	 	Enregistrer cette instance dans le ScenarioManager
  //
  // Implementation:
  //		ScenarioManager est une map de type <canvasNativeID,Scenario>
  //
  // Principe:
  //
  //	 	Lorsque cote java la methode finalize est appeler sur la canvasJava, l'id du CanvasNative associe est passer en natif.
  //		Ce canvasNativeID est passer au ScenarioManager qui se charge de d�rtuire le secenario associ� � cet id
  //
  //		 ScenarioManager::getInstance()->unregister(canvasNativeID) // efface le scenario, fait automatiquement, transparent pour l'utilisateur
  //
  // Conclusion:
  //		Il est necessaire de registrer tout nouveau scenario!
  //		Ceci se fait en appelant la methode d'instance register sur votre scenario apr�s son instanciation
  //
  //			myScenarion->register()
  //


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_CANVAS_JNI ScenarioManager
    {
    public:
	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~ScenarioManager();

	static ScenarioManager* getInstance();

	void registerScenario(Scenario* ptrScenario);

	void unregister(int canvasNativeID);

	Scenario* getScenario(int canvasNativeID);

    private:
	ScenarioManager();
    private:
	//Tools
	map<int, Scenario*> mapPanelIDImageScenario;
	mutex mutexMap;

	// Singleton
	static ScenarioManager* instance;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
