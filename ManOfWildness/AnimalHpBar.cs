using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class AnimalHpBar : MonoBehaviour {

    public Canvas       canvasPrefab;
    public GameObject   barPrefab;
    public GameObject   hpBar;
    public Canvas       canvas;
    public Image        bar;

	AnimalAI animalAI;

    public bool isActiveHpBar       = false;    //HPBar 활성화체크
    public bool isCreativeCanvas    = false;

    float hpBarOffset = 2.5f;

    public float    elapsedTime = 0.0f;
    float           durableTime = 5.0f;

	private void Start()
	{
		animalAI = GetComponent<AnimalAI>();
	}

	public void SetHpBar()
    {
        if(!isCreativeCanvas)
        {
            canvas = Instantiate(canvasPrefab, gameObject.transform);
        }
        hpBar   = Instantiate(barPrefab, canvas.transform);
        bar     = hpBar.GetComponent<Image>();
        isActiveHpBar       = true;
        isCreativeCanvas    = true;
    }
    
	void Update () 
    {
        if (isActiveHpBar && !animalAI.isAnimalDead)
        {
            bar.transform.position = Camera.main.WorldToScreenPoint(transform.position + new Vector3(0, hpBarOffset, 0));
        }
        //hp bar 활성화시간재기
        if(isActiveHpBar)
        {
            elapsedTime += Time.deltaTime;
            if(elapsedTime > durableTime)
            {
                Destroy(hpBar);
                isActiveHpBar = false;
                elapsedTime = 0;
            }
        }
    }
}
