using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameManag : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject[] tileObjects;
    public List<int> tileTypes;
    public Dictionary<GameObject, int> tileToType;
    public Color[] typeToColor;
    public GameObject clickedPrev;
    public int elemCount;
    public Text scoreText;
    void Start()
    {
        gameSetup();
    }

    public void handleClick(GameObject clicked){
        if(clickedPrev == null){
            clickedPrev = clicked;
            return;
        }
        //Debug.Log("Wszedłem w tryb obsługi kliknięcia, clickedPrev= " + clickedPrev.ToString() + " clicked= " + clicked.ToString());
        //Debug.Log("Typ clickedPrev= " + tileToType[clickedPrev] + " typ clicked= " + tileToType[clicked]);
        if(clickedPrev == clicked)
            return;
        else { //chcemy zlikwidować kafelek
            if(tileToType[clicked] == tileToType[clickedPrev]){
                clicked.active = false;
                clickedPrev.active = false;
                elemCount -= 2;
                scoreText.text = "Score: " + (tileObjects.Length - elemCount).ToString();
                if( elemCount == 0 ){
                    gameSetup();
                }
            } //jeśli nie trafimy, to 
            clickedPrev = clicked;
        }
    }

    void GameOver(){
        gameSetup();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void gameSetup(){
        clickedPrev = null;

        tileObjects = GameObject.FindGameObjectsWithTag("TileTag");
        tileTypes = new List<int>();
        tileToType = new Dictionary<GameObject, int>();
        typeToColor = new Color[tileObjects.Length / 4];

        elemCount = tileObjects.Length;

        for(int i = 0; i < tileObjects.Length / 4; i++){
            for(int _ = 0; _ < 4; _++){
                tileTypes.Add(i);
            }
        }

        foreach(var tile in tileObjects){
            int typeIdx = Random.Range(0, tileTypes.Count);
            tileToType.Add(tile, tileTypes[typeIdx]);
            tileTypes.Remove(typeIdx);
        }

        for(int i = 0; i < typeToColor.Length; i++){
            typeToColor[i] = new Color(Random.Range(0, 255)/255.0f, Random.Range(0, 255)/255.0f, Random.Range(0, 255)/255.0f);
        }
        foreach(var tile in tileObjects){
            tile.GetComponent<TileManag>().changeColor( typeToColor[tileToType[tile]] );
            Debug.Log("Zmieniam kolor kafelka " + tile.gameObject + " na " + typeToColor[tileToType[tile]]);
        }
    }
}
