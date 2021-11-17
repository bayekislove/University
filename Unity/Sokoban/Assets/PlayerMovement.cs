using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField]
    float moveForce = 1f;

    // Update is called once per frame
    void FixedUpdate()
    {
        Vector3 delta = new Vector3(0, 0, 0);
        if (Input.GetKey("d"))
        {
            delta = new Vector3(moveForce * Time.deltaTime, 0, 0);
        }

        if (Input.GetKey("a"))
        {
            delta = new Vector3(-moveForce * Time.deltaTime, 0, 0);
        }
        
        if (Input.GetKey("w"))
        {
            delta = new Vector3(0, 0, moveForce * Time.deltaTime);
        }

        if (Input.GetKey("s"))
        {
            delta = new Vector3(0, 0, -moveForce * Time.deltaTime);
        }
        transform.position += delta;
    }
}
