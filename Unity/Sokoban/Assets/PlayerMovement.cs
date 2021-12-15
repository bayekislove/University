using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField]
    bool moving = false;

    [SerializeField]
    GameObject box = null;

    [SerializeField]
    float distance;

    [SerializeField]
    Vector3 directionn;

    public void makeMoveIfPossible(Vector3 direction){
        if(moving){
            return;
        }
        GameObject boxToMove = null;
        foreach(var el in Physics.OverlapSphere(transform.position + direction, 0.0f))
        {
            if(el.gameObject.tag == "BoxTag")
                boxToMove = el.gameObject;
            else if(el.gameObject.tag == "WallTag")
                return;
        }
        if( boxToMove != null ){
            foreach(var el in Physics.OverlapSphere(transform.position + 2 * direction, 0.0f)){
                if(el.gameObject.tag == "BoxTag" || el.gameObject.tag == "WallTag"){
                    return;
                }
            }
            // boxToMove.transform.Translate(direction);
        }
        //transform.Translate(direction);
        moving = true;
        directionn = direction;
        box = boxToMove;
    }
    void Update()
    {
        if( moving ){
            transform.Translate(directionn * 3 * Time.deltaTime);
            if(box != null){
                box.transform.Translate(directionn * 3 * Time.deltaTime);
            }
            distance += 3 * Time.deltaTime;

            if(distance > 1.0f){
                moving = false;
                box = null;
                distance = 0.0f;
            }
        }
        if (Input.GetKeyDown("d"))
        {
            this.makeMoveIfPossible(new Vector3(1, 0, 0)); 
        }

        if (Input.GetKeyDown("a"))
        {
            this.makeMoveIfPossible(new Vector3(-1, 0, 0)); 
        }
        
        if (Input.GetKeyDown("w"))
        {
            this.makeMoveIfPossible(new Vector3(0, 0, 1)); 
        }

        if (Input.GetKeyDown("s"))
        {
            this.makeMoveIfPossible(new Vector3(0, 0, -1)); 
        }
    }
}
