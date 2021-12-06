using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CallPanelControl : MonoBehaviour
{
    public GameObject AcceptButton;
    public Material VideoMaterial;
    private UnityEngine.UI.Image[] panel;

    private float fadeTime;
    // Start is called before the first frame update
    void Start()
    {
        this.AcceptButton.GetComponent<UnityEngine.UI.Button>().onClick.AddListener(AcceptClick);
        this.panel = this.gameObject.GetComponentsInChildren<UnityEngine.UI.Image>();
        fadeTime = 0.3f;
    }

    // Update is called once per frame
    void Update()
    {

    }

    void AcceptClick()
    {
        foreach (UnityEngine.UI.Image image in this.panel)
        {
            image.CrossFadeAlpha(0.0f, fadeTime, true);
        }
        //this.gameObject.GetComponent<Canvas>().enabled = false;
        this.AcceptButton.SetActive(false);
        RenderSettings.skybox = VideoMaterial;
    }
}
