using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    [SerializeField]
    GameObject player;

    [SerializeField]
    Vector3 change;
    // Start is called before the first frame update
    
    public float rotation = 0.0f;
    void Start()
    {
        transform.position = new Vector3(2.5f, 4f, 4.5f);
        Quaternion rot = Quaternion.Euler(30f, rotation, 0f);
        change = transform.position - player.transform.position;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        // Vector3 position = player.transform.position + change;
        // Quaternion rot = Quaternion.Euler(30f, rotation, 0f);
        // transform.SetPositionAndRotation(position, rot);
    }

    void Update()
    {
        // if(Input.GetKeyDown(KeyCode.Space)){
        //     rotation += 10.0f;
        // }
    }
}
