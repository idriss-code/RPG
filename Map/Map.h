#ifndef MAP_H
#define MAP_H


class Map
{
    public:
        Map();
        Map(const Map & source);// constructeur par copie
        Map(int width,int height);
        Map(const char*);
        virtual ~Map();

        int width() const { return m_width; }
        int height() const { return m_height; }
        int tileWidth() const { return m_tileWidth; }
        void setTileWidth(int val) { m_tileWidth = val; }
        int tileHeight() const { return m_tileHeight; }
        void setTileHeight(int val) { m_tileHeight = val; }

        void setTile(int x,int y, int val){tileMap[x][y]=val;}
        int tile(int x,int y) const {return tileMap[x][y];}
        void setObj(int x,int y, int val){objMap[x][y]=val;}
        int obj(int x,int y) const {return objMap[x][y];}

        void loadFromFile(const char*);
        void resizeMap(int width,int height);
        void showTxt()const;
        void fillTile(int);
        void incrementFill();

        Map & operator= (const Map & source);

    protected:

        int m_tileWidth;
        int m_tileHeight;

    private:
        void createMap();
        void freeMap();

        int m_width;
        int m_height;


        int** tileMap;
        int** objMap;
};

#endif // MAP_H
