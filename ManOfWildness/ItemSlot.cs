using System;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class ItemSlot : MonoBehaviour, IPointerClickHandler, IPointerEnterHandler, IPointerExitHandler, IDragHandler, IBeginDragHandler, IEndDragHandler, IDropHandler
{
    [SerializeField] Image image; // 아이템 아이콘이미지를 담을 Image컴포넌트

    public event Action<ItemSlot> OnRightClickEvenet;
	public event Action<ItemSlot> OnPointerEnterEvent;
	public event Action<ItemSlot> OnPointerExitEvent;
	public event Action<ItemSlot> OnBeginDragEvent;
	public event Action<ItemSlot> OnEndDragEvent;
	public event Action<ItemSlot> OnDragEvent;
	public event Action<ItemSlot> OnDropEvent;

	public bool InventorySlot;
	public bool WeaponSlot;
	public bool ConsumeSlot;

	Color normalColor = Color.white;
	Color disabledColor = new Color(1, 1, 1, 0);

	public int amount = 0;
	public Text amountText;

	[SerializeField] Item item; // 슬롯에 있는 아이템
    public Item Item
    {
        get { return item; }
        set
        {
            item = value;

            if(item == null)
            {
                image.color = disabledColor;
			}
            else
            {
                image.sprite = item.icon;
                image.color = normalColor;
            }
        }
    }

	public void RenewAmount()
	{
		amountText.text = amount.ToString();

		if (!(item is Weapon) && !(item is ConstructionItem) && amount > 0)
			amountText.enabled = true;
		else
			amountText.enabled = false;
	}

    protected virtual void OnValidate() // 상속받는 클래스에서 override할수있도록 하기
    {
		if(!Application.isPlaying)
		{
			if (image == null)
				image = GetComponent<Image>();
			if (amountText == null)
			{
				amountText = GetComponentInChildren<Text>();
			}
		}
    }

	public virtual bool CanReceiveItem(Item item)
	{
		return true; // 인벤토리에는 모든아이템 드래그앤드롭 장착가능
	}

    public void OnPointerClick(PointerEventData eventData)
    {
        if (eventData != null && eventData.button == PointerEventData.InputButton.Right) // 마우스 우클릭 했을 때
        {
            if(OnRightClickEvenet != null)
            {
                OnRightClickEvenet(this);
            }
        }
    }

    public void OnPointerEnter(PointerEventData eventData)
    {
		if(OnPointerEnterEvent != null)
		{
			OnPointerEnterEvent(this);
		}
    }

    public void OnPointerExit(PointerEventData eventData)
    {
		if (OnPointerExitEvent != null)
		{
			OnPointerExitEvent(this);
		}
	}

	public void OnBeginDrag(PointerEventData eventData)
	{
		if (OnBeginDragEvent != null)
		{
			OnBeginDragEvent(this);
		}
	}

	public void OnEndDrag(PointerEventData eventData)
	{
		if (OnEndDragEvent != null)
		{
			OnEndDragEvent(this);
		}
	}

	public void OnDrag(PointerEventData eventData)
	{
		if (OnDragEvent != null)
		{
			OnDragEvent(this);
		}
	}

	public void OnDrop(PointerEventData eventData)
	{
		if (OnDropEvent != null)
		{
			OnDropEvent(this);
		}
	}
}