#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
struct punto{
    double x,y;
    punto(double a,double b){
        x=a;y=b;
    }
    punto(){
        x=0;y=0;
    }
    void operator()(double a,double b){
        x=a;y=b;
    }
    void operator=(punto b){
        x=b.x;y=b.y;
    }
    bool operator<(punto c){
        return x<=c.x && y<=c.y;
    }
    bool operator>(punto c){
        return x>=c.x && y>=c.y; 
    }
};
vector<pair<punto,punto> >vec;
struct Quad{
    punto content;
    bool empty;
    bool hoja;
    punto mini,maxi;
    Quad * NO;
    Quad * NE;
    Quad * SO;
    Quad * SE;
    Quad(punto a,punto b){
        empty=1;
        hoja=0;
        mini=a;maxi=b;
        NO=NULL;
        NE=NULL;
        SO=NULL;
        SE=NULL;
        vec.push_back(make_pair(mini,maxi));
    }
    void Agregar(punto p){
        if(empty){
            content=p;
            hoja=1;
            empty=0;
        }
        else{
            if(hoja){
                hoja=0;
                Agregar(content);
            }
            punto r(mini.x,(mini.y+maxi.y)/2);
            punto M((mini.x+maxi.x)/2,(mini.y+maxi.y)/2);
            punto s(maxi.x,(mini.y+maxi.y)/2);
            punto t((mini.x+maxi.x)/2,maxi.y);
            punto v((mini.x+maxi.x)/2,mini.y);
            if(p<M && p>mini){
                if(!SE)SE=new Quad(mini,M);
                else{
                    SE->Agregar(p);
                }
            }
            else if(p<s && p>v){
                if(!SO)SO=new Quad(v,s);
                else{
                    SO->Agregar(p);
                }
            }
            else if(p<maxi && p>M){
                if(!NO)NO=new Quad(M,maxi);
                else{
                    NO->Agregar(p);
                }
            }
            else if(p<t && p>r){
                if(!NE)NE=new Quad(r,t);
                else{
                    NE->Agregar(p);
                }
            }
        }
    }
};
pair<punto,punto> limit(vector<punto> data){
    punto mini;
    punto maxi;
    for(int i=0;i<data.size();++i){
        if(i==0){
            mini=data[0];
            maxi=data[0];
        }
        if(maxi.x<data[i].x){
            maxi.x=data[i].x;
        }
        if(maxi.y<data[i].y){
            maxi.y=data[i].y;
        }
        if(mini.x>data[i].x){
            mini.x=data[i].x;
        }
        if(mini.y>data[i].y){
            mini.y=data[i].y;
        }
    }
    return make_pair(mini,maxi);
}
int main(){

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;

    int a;
    cin>>a;
    pair<punto,punto>l;
    vector<punto>data;
    for(int i=0;i<a;i++){
        double g,h;
        cin>>g>>h;
        data.push_back(punto(g,h));
    }
    l=limit(data);
    Quad Q(l.first,l.second);
    for(int i=0;i<data.size();i++){
        Q.Agregar(data[i]);
    }
    for(int i=0;i<vec.size();i++){
        cout<<vec[i].first.x<<" "<<vec[i].first.y;
        cout<<"        "<<vec[i].second.x<<vec[i].second.y<<endl;
    }
}