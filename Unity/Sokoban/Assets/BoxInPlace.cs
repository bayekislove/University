using UnityEngine;

public class BoxInPlace : MonoBehaviour
{
    [SerializeField]
    GameObject visualSign;

    [SerializeField]
    LevelManagement levelManagement;

    private void OnCollisionEnter(Collision collisionInfo)
    {
        if(collisionInfo.gameObject.tag == "BoxTag")
        {
            GetComponent<AudioSource>().Play();
            visualSign.GetComponent<Renderer>().material.color = Color.green;
            levelManagement.handleBoxInserted(collisionInfo.collider.gameObject);

        }
    }

    private void OnCollisionExit(Collision collisionInfo){
        if(collisionInfo.gameObject.tag == "BoxTag")
        {
            visualSign.GetComponent<Renderer>().material.color = new Color(0.8396226f, 0.379124f, 0.05069415f, 1f);
            levelManagement.handleBoxRemoved(collisionInfo.collider.gameObject);
        }
    }
}