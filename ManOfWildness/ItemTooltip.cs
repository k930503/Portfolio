using UnityEngine;
using UnityEngine.UI;


public class ItemTooltip : MonoBehaviour
{
	[SerializeField] Text itemNameText;
    [SerializeField] Text itemTypeText;
    [SerializeField] Text itemDescriptionText;

    // 아이템에 마우스오버 했을 때 활성화 시켜주고 텍스트정보 입력해주는 함수
    public void ShowToolTip(Item item)
    {
        itemNameText.text = item.itemName;

        if(item is Weapon)
        {
            itemTypeText.text = ((Weapon)item).itemType.ToString();
        }
        else if(item is ConsummableItem)
        {
            itemTypeText.text = ((ConsummableItem)item).itemType.ToString();
        }
        else if(item is ConstructionItem)
        {
			itemTypeText.text = ((ConstructionItem)item).itemType.ToString();
		}

        itemDescriptionText.text = item.description;

        gameObject.SetActive(true);
    }

    // 마우스오버 끝났을때 다시 비활성화 시켜주는 함수
    public void HideTooltip()
    {
        gameObject.SetActive(false);
    }
}
