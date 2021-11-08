using UnityEngine;

public class TileManag : MonoBehaviour
{
    // public GameObject upLeft;
    // public GameObject upRight;
    // public GameObject downLvl;
    public GameObject upLvl;
    // public GameObject downLeft;
    // public GameObject downRight;
    public GameObject leftUp;
    public GameObject leftDown;

    public GameObject rightUp;
    public GameObject rightDown;
    public GameManag gameLogic;

    private bool isAccessible()
    {
        return ( !( (leftUp != null && leftUp.active) || (leftDown != null && leftDown.active) ) || 
                 !( (rightUp != null && rightUp.active) || (rightDown != null && rightDown.active) ));

    }

    // Start is called before the first frame update
    void Start()
    {
        // if(isAccessible()){
        //     GetComponent<SpriteRenderer>().color = Color.red;
        // }
    }

    public void changeColor(Color32 c)
    {
        //Debug.Log("Chcę zmienić na " + c);
        GetComponent<SpriteRenderer>().color = c;
    }

    // Update is called once per frame
    void Update()
    {

    }

    void OnMouseDown(){
        Debug.Log(GetComponent<SpriteRenderer>().color);
        if( isAccessible() )
            gameLogic.handleClick(this.gameObject);
    }
}
