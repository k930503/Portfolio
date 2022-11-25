using UnityEngine;

public class EquipmentSlot : ItemSlot
{
    public ItemTypes EquippableType;

    protected override void OnValidate()
    {
        base.OnValidate();

		if (!Application.isPlaying)
			gameObject.name = EquippableType.ToString() + " Slot";
    }

	public override bool CanReceiveItem(Item item) // 드래그 앤 드롭으로 EquipmentSlot에 아이템 드래그할 때 아이템 장착이 가능한 슬롯인지 판단하는 함수
	{
		if(item is Weapon)
		{
			return (item as Weapon).itemType == EquippableType;
		}
		else if (item is ConsummableItem)
		{
			return (item as ConsummableItem).itemType == EquippableType;
		}
		else
		{
			return false;
		}
	}
}
