using UnityEngine;
using UnityEngine.EventSystems;
using System.Collections;
using System;

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

    float globalRotation = 0.0f;

    public void makeMoveIfPossible(Vector3 direction){
        if(moving){
            return;
        }
        GameObject boxToMove = null;
        Vector3 checkVect = new Vector3(direction.x, 0, direction.z);
        Vector3 playVect = new Vector3(transform.position.x, 1, transform.position.z);
        foreach(var el in Physics.OverlapSphere(playVect + checkVect, 0.2f))
        {
            if(el.gameObject.tag == "BoxTag")
                boxToMove = el.gameObject;
            else if(el.gameObject.tag == "WallTag")
                return;
        }
        if( boxToMove != null ){
            foreach(var el in Physics.OverlapSphere(playVect + 2 * checkVect, 0.2f)){
                if(el.gameObject.tag == "BoxTag" || el.gameObject.tag == "WallTag"){
                    return;
                }
            }
            boxToMove.GetComponent<AudioSource>().Play();
            // boxToMove.transform.Translate(direction);
        }
        //transform.Translate(direction);
        moving = true;
        directionn = direction;
        box = boxToMove;
    }
    
    private double getNearestHalf(float inp){
        Boolean nonNegative = inp < 0;
        float pom = Math.Abs(inp) % 1; //get decimal part
        if(pom == 0)
            return inp;
        if( pom < 0.25 ){
            return nonNegative ? Math.Floor(inp) : Math.Ceiling(inp);
        } else if (pom < 0.75){
            return nonNegative ? Math.Floor(inp) + 0.5f : Math.Floor(inp) + 0.5f;
        } else {
            return nonNegative ? Math.Floor(inp) + 1f : Math.Floor(inp) + 1f;
        }
    }

    public void restoreProperPosition(GameObject obj){
        float x = obj.transform.position.x;
        float y = obj.transform.position.y;
        float z = obj.transform.position.z;
        x = (float)getNearestHalf(x);
        z = (float)getNearestHalf(z);
        if( (y % 1) < 0.5 ){
            y = (float)Math.Floor((double)y);
        } else {
            y = (float)Math.Ceiling((double)y);
        }
        obj.transform.position = new Vector3(x, y, z);
    }

    public IEnumerator delayedRotate(float f){
        float fd = globalRotation + f;
        float ff = globalRotation;
        for(int i = 0; i < 30; i++){
            ff = 0.9f * ff + 0.1f * fd;
            transform.localRotation = Quaternion.Euler(0, ff, 0);
            yield return new WaitForEndOfFrame();
        }
        globalRotation = fd;
    }
    
    void Start(){
        Application.targetFrameRate = 30;
    }

    void Update()
    {
        if( moving ){
            if(box != null){
                Vector3 moveVect = new Vector3(directionn.x, 0, directionn.z); 
                box.transform.Translate(moveVect * 5 * Time.deltaTime);
                transform.Translate(moveVect * 5 * Time.deltaTime);
            } else {
                transform.Translate(directionn * 5 * Time.deltaTime);
            }
            distance += 5 * Time.deltaTime;

            if(distance > 1.0f){
                moving = false;
                //Debug.Log(transform.position);
                restoreProperPosition(this.gameObject);
                if(box != null)
                    restoreProperPosition(box);
                box = null;
                distance = 0.0f;
            }
            if(distance > 0.5f){
                directionn = new Vector3(directionn.x, -Math.Abs(directionn.y), directionn.z);
            }
        }
        Vector3 moveVector = new Vector3(0, 0, 0);
        if (Input.GetKey("d"))
        {
            moveVector += new Vector3(1, 2, 0);
            StartCoroutine(delayedRotate(90.0f));
        }

        if (Input.GetKey("a"))
        {
            moveVector += new Vector3(-1, 2, 0); 
            StartCoroutine(delayedRotate(-90.0f));
        }
        
        if (Input.GetKey("w"))
        {
            moveVector += new Vector3(0, 2, 1); 
            //StartCoroutine(delayedRotate(0.0f));
        }

        if (Input.GetKey("s"))
        {
            moveVector += new Vector3(0, 2, -1); 
            //StartCoroutine(delayedRotate(180.0f));
        }
        this.makeMoveIfPossible( moveVector ); 
    }
}
