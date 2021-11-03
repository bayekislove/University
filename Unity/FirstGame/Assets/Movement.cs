using UnityEngine;

public class Movement : MonoBehaviour
{
    public Rigidbody rigidbody;

    public float fwdForce = 1000f;
    public float sideForce = 300f;

    // Update is called once per frame
    void FixedUpdate()
    {
        rigidbody.AddForce(0, 0, fwdForce * Time.deltaTime);

        if (Input.GetKey("d"))
        {
            rigidbody.AddForce(sideForce * Time.deltaTime, 0, 0, ForceMode.VelocityChange);
        }

        if (Input.GetKey("a"))
        {
            rigidbody.AddForce(-sideForce * Time.deltaTime, 0, 0, ForceMode.VelocityChange);
        }
    }
}
