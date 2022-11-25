using System;
using System.Collections.Generic;
using UnityEngine;

public class Inventory : MonoBehaviour {

    public List<Item> startingItems;       // 인벤토리 슬롯에 있는 아이템 리스트
    [SerializeField] Transform itemParent; // 인벤토리 슬롯들의 부모 오브젝트의 트랜스폼 컴포넌트
    public ItemSlot[] itemSlots; // 인벤토리 슬롯들이 가진 ItemSlot 컴포넌트의 배열

	public event Action<ItemSlot> OnRightClickEvenet;
	public event Action<ItemSlot> OnPointerEnterEvent;
	public event Action<ItemSlot> OnPointerExitEvent;
	public event Action<ItemSlot> OnBeginDragEvent;
	public event Action<ItemSlot> OnEndDragEvent;
	public event Action<ItemSlot> OnDragEvent;
	public event Action<ItemSlot> OnDropEvent;

	private void Start()
    {
        for (int i = 0; i < itemSlots.Length; i++)
        {
            itemSlots[i].OnRightClickEvenet += OnRightClickEvenet;
			itemSlots[i].OnPointerEnterEvent += OnPointerEnterEvent;
			itemSlots[i].OnPointerExitEvent += OnPointerExitEvent;
			itemSlots[i].OnBeginDragEvent += OnBeginDragEvent;
			itemSlots[i].OnEndDragEvent += OnEndDragEvent;
			itemSlots[i].OnDragEvent += OnDragEvent;
			itemSlots[i].OnDropEvent += OnDropEvent;
		}

        SetStartingItems();
    }

    private void OnValidate()
    {
        if(itemParent != null)
        {
            itemSlots = itemParent.GetComponentsInChildren<ItemSlot>(); // itemSlots 변수 초기화
        }

		if(!Application.isPlaying)
		{
			SetStartingItems();
		}
    }

    private void SetStartingItems()
    {
		// TODO 저장된 아이템 불러오기
        int i = 0;
        for (; i < startingItems.Count && i < itemSlots.Length; i++)
        {
            itemSlots[i].Item = Instantiate(startingItems[i]);
			itemSlots[i].RenewAmount();

            if (itemSlots[i].Item is Weapon)
            {
                itemSlots[i].amountText.text = Mathf.Round((itemSlots[i].Item as Weapon).durability) + "%";
                itemSlots[i].amountText.enabled = true;
            }
        }

        for (; i < itemSlots.Length; i++)
        {
            itemSlots[i].Item = null;
			itemSlots[i].RenewAmount();
		}
    }

    public bool AddItem(Item item, int amount = 1) // 인벤토리에 아이템 추가하기
    {
		for (int i = 0; i < itemSlots.Length; i++)
		{
            if (itemSlots[i].Item != null)
			{
				if (itemSlots[i].Item is Weapon)
				{
					itemSlots[i].amountText.text = Mathf.Round((itemSlots[i].Item as Weapon).durability) + "%";
					itemSlots[i].amountText.enabled = true;
				}

				if (itemSlots[i].Item.itemName == item.itemName)
				{
					if (itemSlots[i].amount < itemSlots[i].Item.maxStack)
					{
						if(itemSlots[i].amount + amount > itemSlots[i].Item.maxStack)
						{
							int remainingAmount = itemSlots[i].amount + amount - itemSlots[i].Item.maxStack;

							for (int j = 0; j < itemSlots.Length; j++)
							{
								if(itemSlots[j].Item == null)
								{
									itemSlots[j].Item = item;
									itemSlots[j].amount = remainingAmount;
									itemSlots[j].RenewAmount();
									break;
								}
								else
								{
									if (j == itemSlots.Length - 1)
										return false;
								}
							}

							itemSlots[i].amount = itemSlots[i].Item.maxStack;
							itemSlots[i].RenewAmount();
						}
						else
						{
							itemSlots[i].amount += amount;
							itemSlots[i].RenewAmount();
						}

                        return true;
					}
				}
			}
		}

		for (int i = 0; i < itemSlots.Length; i++)
        {
            if(itemSlots[i].Item == null)
            {
                itemSlots[i].Item = item;
				itemSlots[i].amount += amount;
				itemSlots[i].RenewAmount();

                if (itemSlots[i].Item is Weapon)
                {
                    itemSlots[i].amountText.text = Mathf.Round((itemSlots[i].Item as Weapon).durability) + "%";
                    itemSlots[i].amountText.enabled = true;
                }
                return true;
            }
        }

        return false;
    }

    public bool RemoveItem(Item item) // 인벤토리에서 아이템 빼기
    {
		for (int i = 0; i < itemSlots.Length; i++)
		{
			if (itemSlots[i].Item == item)
			{
				itemSlots[i].Item = null;
				itemSlots[i].amount = 0;
				itemSlots[i].RenewAmount();
				return true;
			}
		}
		return false;
	}

    public bool IsFull() // 인벤토리가 꽉찼는지 여부를 반환해주는 함수
    {
		for (int i = 0; i < itemSlots.Length; i++)
		{
			if (itemSlots[i].Item == null)
			{
				return false;
			}
		}
		return true;
	}

    public void AddItemInSpecificSlot(Item item, ItemSlot itemSlot)
    {
        itemSlot.Item = item;

        if (itemSlot.Item is Weapon)
        {
            itemSlot.amountText.text = Mathf.Round((itemSlot.Item as Weapon).durability) + "%";
            itemSlot.amountText.enabled = true;
        }
    }

    public bool ContainItem(Item item, int amount)
    {
		for (int i = 0; i < itemSlots.Length; i++)
        {
			if(itemSlots[i].Item != null)
			{
				if (itemSlots[i].Item.itemName == item.itemName)
				{
					if (itemSlots[i].amount >= amount)
						return true;
					else
						continue;
				}
			}
        }
        return false;
    }


    // TODO 게임 이어할 때 데이터 로드해주는 함수
    private void LoadData()
    {
        if (DataManagement.DataManager.Instance != null)
        {
            DataManagement.DataManager.Instance.Load();
        }

        
    }
}
