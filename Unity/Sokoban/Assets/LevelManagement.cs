using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections.Generic;
public class LevelManagement : MonoBehaviour
{
    [SerializeField] 
    int maxBoxes;
    [SerializeField]
    int maxLevel;
    [SerializeField]
    int currentLevel;

    private HashSet<GameObject> boxesOnPlace;

    public void Start()
    {
        boxesOnPlace = new HashSet<GameObject>();
    }

    void Update()
    {
        if(Input.GetKeyDown("r")){
            SceneManager.LoadSceneAsync("Level" + currentLevel.ToString());
        }   
    }
    public void handleBoxInserted(GameObject box)
    {
        boxesOnPlace.Add(box);
        if(boxesOnPlace.Count == maxBoxes){
            if(currentLevel == maxLevel){
                Debug.Log("YOU WON!");
                SceneManager.LoadSceneAsync("GameOverScene");
                SceneManager.UnloadSceneAsync("Level" + (currentLevel--).ToString());
            } else {
                currentLevel++;
                SceneManager.LoadSceneAsync("Level" + currentLevel.ToString());
                SceneManager.UnloadSceneAsync("Level" + (currentLevel--).ToString());
            }
        }
    }

    public void handleBoxRemoved(GameObject box)
    {
        boxesOnPlace.Remove(box);
    }
}
