using UnityEngine.UI;
using UnityEngine;

public class Timer : MonoBehaviour
{
    public Text timerText;
    private float startTime;

    // Start is called before the first frame update
    void Start()
    {
        startTime = Time.time;
        Time.fixedTime;
    }

    // Update is called once per frame
    void Update()
    {
        float elapsedTime = Time.time - Time.fixedTime;
        string minutes = ((int)elapsedTime / 60).ToString();
        string seconds = ((int)elapsedTime % 60).ToString();
        timerText.text = "Time: " + minutes + ":" + seconds;
    }
}
