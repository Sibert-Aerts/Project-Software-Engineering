#include "tinyxml/tinyxml.h"
#include <iostream>
#include "tinyxml/tinystr.h"
#include <stdlib.h>
#include <string>

using namespace std;

enum TileType {Empty, Player, Barrel, Wall};

class Tile{
public:
	TileType Type;
	bool Movable;
	
	Tile(){
		Type = Empty;
		Movable = false;
	}

	Tile(TileType type, bool movable){
		Type = type;
		Movable = movable;
	}
	
	void set(TileType type, bool movable){
		Type = type;
		Movable = movable;
	}
	
	void set(TileType type){
		Type = type;
		Movable = false;
	}
};


class Board{
public:
	int Width, Height;
	Tile** Tiles;
	string Name;

	Board(const char* xmldoc){
	
		TiXmlDocument doc;
		if(!doc.LoadFile(xmldoc))
		{
			cerr << doc.ErrorDesc() << endl;
		}
		TiXmlElement* Board = doc.FirstChildElement();
		if(Board == NULL)
		{
		cerr << "Failed to load file: No board element." << endl;
		doc.Clear();
		}
	
		for(TiXmlElement* elem = Board->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
		{
			string elemName = elem->Value();
			if(elemName == "NAAM"){
				Name = elem->GetText();
			}
			
			if(elemName == "LENGTE"){
				Height = 10;
			}
			
			if(elemName == "BREEDTE"){
				Width = 10;
			}
		}
		
		// Create an array of tiles
		Tiles = new Tile*[Width];
		for(int i = 0; i < Width; i++){
			Tiles[i] = new Tile [Height];
		}

		int PlayerX = atoi(Board->FirstChildElement("SPELER")->Attribute("x"));
		int PlayerY = atoi(Board->FirstChildElement("SPELER")->Attribute("y"));
		const char* PlayerName = Board->FirstChildElement("SPELER")->FirstChildElement()->GetText();
		
		Tiles[PlayerX][PlayerY].set(Player);
		
		for(TiXmlElement* elem = Board->FirstChildElement("OBSTAKEL"); elem != NULL; elem = elem->NextSiblingElement())
		{
			int TileX = atoi(elem->Attribute("x"));
			int TileY = atoi(elem->Attribute("y"));
			bool TileMovable = (elem->Attribute("beweegbaar") == "true");
			
			string TileTypeStr = elem->FirstChildElement()->GetText();
			TileType Type;
				if( TileTypeStr == "ton"){
					Type = Barrel;
				} else if (TileTypeStr == "muur"){
					Type = Wall;
				}
			Tiles[TileX][TileY].set(Type, TileMovable);
		}
	}
	
	friend ostream& operator<<(ostream& os, const Board& bd){

		for(int i = 0; i < bd.Width; i++){
			for(int j= 0; j < bd.Height;j++)
			{
				if(bd.Tiles[i][j].Type == Empty){
					os << ' '<< ' '; 	
				}
				else if(bd.Tiles[i][j].Type == Player){
					os <<'X'<< ' ';
				}
				else if(bd.Tiles[i][j].Type == Barrel ){
					os <<'O'<< ' ';
				}
				else if(bd.Tiles[i][j].Type == Wall){
					os <<'#'<< ' ';
				}

			}
			os << endl;
		}
		return os;
	}
};
















