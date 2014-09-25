#ifndef APPARANCE_H_
#define APPARANCE_H_
#include "envGraph.h"
#include "Color.h"

#include <string>
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/**
 * @enum TypeConnector
 * Define only for ploylines the appearance of the figure.
 */
enum TypeConnector
    {
    TYPE_LINES,
    TYPE_POINTS
    };


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH Apparance
    {
    public:
	Apparance(Color foreground=Color::WHITE,Color background=Color::BLACK,TypeConnector connectorType=TYPE_LINES);

	Color getForeground() const;
	Color getBackground() const;
	TypeConnector getConnectorType() const;

	void setForeground(Color color);
	void setBackground(Color color);
	void setConnectorType(TypeConnector connectorType);

    private :
	Color foreground;
	Color background;
	TypeConnector connectorType;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
