using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnimalState : MonoBehaviour {

	public string nameValue;
	public float hp;
	public int power;
	public int walkSpeed;
	public int runSpeed;
	public int viewRange;
	public int viewAngle;
	public int minimumItemDropCount;
	public int maximumItemDropCount;


	private void Start()
	{
        State tableState = AnimalDataManager.instance.GetObjectState(nameValue);

        hp                   = tableState.hp;
		power                = tableState.power;
		walkSpeed            = tableState.walkSpeed;
		runSpeed             = tableState.runSpeed;
		viewRange            = tableState.viewRange;
		viewAngle            = tableState.viewAngle;
		minimumItemDropCount = tableState.minimumItemDropCount;
		maximumItemDropCount = tableState.maximumItemDropCount;

    }
}
