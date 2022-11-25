using UnityEngine;
using UnityEngine.UI;

public class InventoryManager : MonoBehaviour {

    [SerializeField] Inventory inventory;
    [SerializeField] WeaponPanel weaponPanel;
    [SerializeField] ConsumePanel consumePanel;

	[SerializeField] ItemTooltip itemTooltip;

    [SerializeField] Image draggableItem;
    ItemSlot draggedItemSlot;

    public GameObject constructionObject;
    int groundLayer;
    float maxPlacementDistance = 15.0f;
    float mouseWheelRotation = 0.0f;
    float rotationSpeed = 10.0f;
    [SerializeField] AudioClip hammeringSFX;

    #region 싱글톤
    static InventoryManager instance = null;
    public static InventoryManager Instance
    {
        get
        {
            return instance;
        }
    }

    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
            // Mouse Over (마우스 아이템위에 올려져있을 때)
            inventory.OnPointerEnterEvent += ShowToolTip;
            inventory.OnPointerExitEvent += HideToolTip;
            weaponPanel.OnPointerEnterEvent += ShowToolTip;
            weaponPanel.OnPointerExitEvent += HideToolTip;
            consumePanel.OnPointerEnterEvent += ShowToolTip;
            consumePanel.OnPointerExitEvent += HideToolTip;

            // Right Click (마우스 우클릭)
            inventory.OnRightClickEvenet += EquipWeaponFromInventory;
            weaponPanel.OnRightClickEvenet += UnequipFromWeaponPanel;
            inventory.OnRightClickEvenet += EquipConsummableItemFromInventory;
            consumePanel.OnRightClickEvenet += UnequipFromConsumePanel;
            inventory.OnRightClickEvenet += PlaceConstructionObject;

            // Begin Drag (마우스 왼쪽버튼으로 드래그 시작)
            inventory.OnBeginDragEvent += BeginDrag;
            weaponPanel.OnBeginDragEvent += BeginDrag;
            consumePanel.OnBeginDragEvent += BeginDrag;

            // Drag
            inventory.OnDragEvent += Drag;
            weaponPanel.OnDragEvent += Drag;
            consumePanel.OnDragEvent += Drag;

            // End Drag
            inventory.OnEndDragEvent += EndDrag;
            weaponPanel.OnEndDragEvent += EndDrag;
            consumePanel.OnEndDragEvent += EndDrag;

            // Drop
            inventory.OnDropEvent += Drop;
            weaponPanel.OnDropEvent += Drop;
            consumePanel.OnDropEvent += Drop;

            groundLayer = 1 << LayerMask.NameToLayer("Ground");
        }
        else
        {
            Destroy(gameObject);
        }
    }

    private void OnDestroy()
    {
        if (instance == this)
        {
            instance = null;
        }
    }
    #endregion


    // 아이템 툴팁 관련 ----------------------------------------------------------------------------------------------------------------------------------------
    private void ShowToolTip(ItemSlot itemSlot)
	{
		if(itemSlot.Item != null)
		{
			itemTooltip.ShowToolTip(itemSlot.Item);
		}
	}
	private void HideToolTip(ItemSlot itemSlot)
	{
		itemTooltip.HideTooltip();
	}
    // 아이템 툴팁 관련 ----------------------------------------------------------------------------------------------------------------------------------------



    // 무기슬롯 관련 ----------------------------------------------------------------------------------------------------------------------------------------
    private void EquipWeaponFromInventory(ItemSlot itemSlot)
    {
        if(itemSlot.Item is Weapon)
        {
            EquipWeapon(itemSlot.Item as Weapon);
            itemTooltip.HideTooltip();
        }
    }
    private void UnequipFromWeaponPanel(ItemSlot itemSlot)
    {
        if(itemSlot.Item is Weapon)
        {
            UnequipWeapon(itemSlot.Item as Weapon);
            itemTooltip.HideTooltip();
        }
    }
    // 무기슬롯 관련 ----------------------------------------------------------------------------------------------------------------------------------------


    // 소비슬롯 관련 ----------------------------------------------------------------------------------------------------------------------------------------
    private void EquipConsummableItemFromInventory(ItemSlot itemSlot)
	{
		if(itemSlot.Item is ConsummableItem)
		{
			EquipComsummableItem(itemSlot, itemSlot.amount);
            itemTooltip.HideTooltip();
        }
	}

	private void UnequipFromConsumePanel(ItemSlot itemSlot)
	{
		if (itemSlot.Item is ConsummableItem)
		{
			UnequipComsummableItem(itemSlot);
            itemTooltip.HideTooltip();
        }
	}
    // 소비슬롯 관련 ----------------------------------------------------------------------------------------------------------------------------------------


    // 건축물 설치 관련 ----------------------------------------------------------------------------------------------------------------------------------------
    public void PlaceConstructionObject(ItemSlot itemSlot)
    {
        if(itemSlot.Item is ConstructionItem)
        {
            if ((itemSlot.Item as ConstructionItem).itemType == ItemTypes.Construction)
            {
                constructionObject = Instantiate((itemSlot.Item as ConstructionItem).GetconstructionItemPrefab());
                if (itemSlot.Item.itemName == "Camp Fire")
                {
                    if (GameManager.Instance.campFire != null)
                        Destroy(GameManager.Instance.campFire);

                    GameManager.Instance.campFire = constructionObject;
                }
                constructionObject.transform.position = Input.mousePosition;
                inventory.RemoveItem(itemSlot.Item);
            }
        }        
    }
    // 건축물 설치 관련 ----------------------------------------------------------------------------------------------------------------------------------------



    // 드래그 앤 드롭 관련 ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    public void BeginDrag(ItemSlot itemSlot)
    {
        if(itemSlot.Item != null)
        {
            draggedItemSlot = itemSlot;
            draggableItem.sprite = itemSlot.Item.icon;
            draggableItem.transform.position = Input.mousePosition;
            draggableItem.enabled = true;
			draggableItem.raycastTarget = false;
		}
    }   
    
    public void Drag(ItemSlot itemSlot)
    {
        if(draggableItem.enabled)
        {
            draggableItem.transform.position = Input.mousePosition;
        }
    }

    public void EndDrag(ItemSlot itemSlot)
    {
        draggedItemSlot = null;
        draggableItem.enabled = false;
		draggableItem.raycastTarget = true;
	}

	private void Drop(ItemSlot itemSlotToDrop)
	{
		if (draggedItemSlot == null) return;

		Item draggedItem = draggedItemSlot.Item;
		Item itemToBeSwapped = itemSlotToDrop.Item;

		if (itemToBeSwapped == null) // 드래그되는 아이템이 드랍된 곳에 아이템이 없다면
		{
			if (itemSlotToDrop.CanReceiveItem(draggedItemSlot.Item)) // 드랍 될 슬롯에 아이템이 장착될수 있는 곳인지 판단
			{
				if (itemSlotToDrop.WeaponSlot)       // 1. 드랍 될 곳이 무기슬롯이라면
				{
					if ((draggedItem as Weapon).itemType == (itemSlotToDrop as EquipmentSlot).EquippableType)
					{
						EquipWeapon(draggedItem as Weapon);
					}
				}
				else if (itemSlotToDrop.ConsumeSlot) // 2. 드랍 될 곳이 소비슬롯이라면
				{
					if ((draggedItem as ConsummableItem).itemType == (itemSlotToDrop as EquipmentSlot).EquippableType)
					{
						if(draggedItemSlot.InventorySlot)
						{
							itemSlotToDrop.amount += draggedItemSlot.amount;
							inventory.RemoveItem(draggedItem);
							consumePanel.AddItemInSpecificSlot(draggedItem as ConsummableItem, itemSlotToDrop);
						}
						else // 소비슬롯에서 소비슬롯으로 드래그앤드롭하는 경우
						{
							itemSlotToDrop.amount += draggedItemSlot.amount;
							consumePanel.RemoveItem(draggedItem as ConsummableItem);
							consumePanel.AddItemInSpecificSlot(draggedItem as ConsummableItem, itemSlotToDrop);
						}
					}
				}
				else                                // 3. 드랍 될 곳이 인벤토리 슬롯이라면
				{
					if (draggedItemSlot.WeaponSlot)       // 드래그 되는 아이템이 무기슬롯에 있던 아이템이라면
					{
						weaponPanel.RemoveItem(draggedItem as Weapon);
						inventory.AddItemInSpecificSlot(draggedItem, itemSlotToDrop);
					}
					else if (draggedItemSlot.ConsumeSlot) // 드래그 되는 아이템이 소비슬롯에 있던 아이템이라면
					{
						itemSlotToDrop.amount = draggedItemSlot.amount;
						itemSlotToDrop.RenewAmount();

						consumePanel.RemoveItem(draggedItem as ConsummableItem);
						inventory.AddItemInSpecificSlot(draggedItem, itemSlotToDrop);
					}
					else                                 // 드래그 되는 아이템이 인벤토리 슬롯에 있던 아이템이라면
					{
						int draggedAmount = draggedItemSlot.amount;

						inventory.RemoveItem(draggedItem);
                        itemSlotToDrop.amount = draggedAmount;
                        itemSlotToDrop.RenewAmount();
                        inventory.AddItemInSpecificSlot(draggedItem, itemSlotToDrop);				
					}
				}
			}		
		}
		else   // 드래그되는 아이템이 드랍된 곳에 아이템이 있다면
		{
			if (itemSlotToDrop.CanReceiveItem(draggedItemSlot.Item) && draggedItemSlot.CanReceiveItem(itemSlotToDrop.Item)) // 아이텝 스왑 가능한지 체크
			{
				if (itemSlotToDrop.WeaponSlot)         // 1. 드랍 될 곳이 무기슬롯이라면
				{
					EquipWeapon(draggedItem as Weapon);
				}

				else if (itemSlotToDrop.ConsumeSlot)   // 2. 드랍 될 곳이 소비슬롯이라면
				{
					if(draggedItemSlot.InventorySlot) // 인벤토리로부터 드래그앤 드롭 되는 경우
					{
						if (draggedItem.itemName != itemToBeSwapped.itemName) // 다른 종류의 소비아이템인 경우 교체하기
						{
							int draggedAmount = draggedItemSlot.amount;
							int swappedAmount = itemSlotToDrop.amount;

							inventory.RemoveItem(draggedItem);

							draggedItemSlot.amount = swappedAmount;
							inventory.AddItemInSpecificSlot(itemToBeSwapped, draggedItemSlot);
							draggedItemSlot.RenewAmount();

							itemSlotToDrop.amount = draggedAmount;
							consumePanel.AddItemInSpecificSlot(draggedItem as ConsummableItem, itemSlotToDrop);						
						}
						else // 같은 종류의 아이템인 경우 merge하기
						{
							if (itemSlotToDrop.amount + draggedItemSlot.amount > draggedItem.maxStack)
							{
								int remainingAmount = itemSlotToDrop.amount + draggedItemSlot.amount - draggedItem.maxStack;

								itemSlotToDrop.amount = draggedItem.maxStack;
								itemSlotToDrop.RenewAmount();

								
								draggedItemSlot.amount = remainingAmount;
								draggedItemSlot.RenewAmount();
							}
							else
							{
								itemSlotToDrop.amount += draggedItemSlot.amount;
								itemSlotToDrop.RenewAmount();
								inventory.RemoveItem(draggedItem);
							}
						}
					}
					else // 소비슬롯에서 소비슬롯으로 드래그앤 드롭하는 경우
					{
						if (draggedItem.itemName != itemToBeSwapped.itemName) // 다른 종류의 소비아이템인 경우 교체하기
						{
							int draggedAmount = draggedItemSlot.amount;
							int swappedAmount = itemSlotToDrop.amount;

							draggedItemSlot.amount = swappedAmount;
							itemSlotToDrop.amount = draggedAmount;

							consumePanel.AddItemInSpecificSlot(draggedItem as ConsummableItem, itemSlotToDrop); 
							consumePanel.AddItemInSpecificSlot(itemToBeSwapped as ConsummableItem, draggedItemSlot);
						}
						else // 같은 종류의 아이템인 경우 merge하기
						{
							if (itemSlotToDrop.amount + draggedItemSlot.amount > draggedItem.maxStack)
							{
								int remainingAmount = itemSlotToDrop.amount + draggedItemSlot.amount - draggedItem.maxStack;

								itemSlotToDrop.amount = draggedItem.maxStack;
								itemSlotToDrop.RenewAmount();
				
								draggedItemSlot.amount = remainingAmount;
								draggedItemSlot.RenewAmount();
							}
							else
							{
								itemSlotToDrop.amount += draggedItemSlot.amount;
								itemSlotToDrop.RenewAmount();

								consumePanel.RemoveItem(draggedItem as ConsummableItem);
							}
						}
					}
					
				}

				else if (itemSlotToDrop.InventorySlot) // 3. 드랍 될 목적지가 인벤토리 슬롯이라면
				{
					if (draggedItemSlot.WeaponSlot)       // 드래그 되고있는 아이템이 무기슬롯에 있던 아이템이라면
					{
						EquipWeapon(itemToBeSwapped as Weapon);
					}
					else if (draggedItemSlot.ConsumeSlot) // 드래고 되고있는 아이템이 소비슬롯에 있던 아이템이라면
					{
						if (draggedItem.itemName != itemToBeSwapped.itemName) // 다른 종류의 소비아이템인 경우 교체하기
						{
							int draggedAmount = draggedItemSlot.amount;
							int swappedAmount = itemSlotToDrop.amount;

							inventory.RemoveItem(itemToBeSwapped);
							inventory.AddItemInSpecificSlot(draggedItem, itemSlotToDrop);
							itemSlotToDrop.amount = draggedAmount;
							itemSlotToDrop.RenewAmount();

							draggedItemSlot.Item = itemToBeSwapped;
							draggedItemSlot.amount = swappedAmount;
							draggedItemSlot.RenewAmount();
						}
						else // 같은 종류의 아이템인 경우 merge하기
						{
							if (itemSlotToDrop.amount + draggedItemSlot.amount > draggedItem.maxStack)
							{
								int remainingAmount = itemSlotToDrop.amount + draggedItemSlot.amount - draggedItem.maxStack;

								itemSlotToDrop.amount = draggedItem.maxStack;
								itemSlotToDrop.RenewAmount();

								draggedItemSlot.amount = remainingAmount;
								draggedItemSlot.RenewAmount();
							}
							else
							{
								itemSlotToDrop.amount += draggedItemSlot.amount;
								itemSlotToDrop.RenewAmount();

								draggedItemSlot.amount = 0;
								draggedItemSlot.RenewAmount();
								draggedItemSlot.Item = null;
							}
						}
					}
					else // 드래고 되고있는 아이템이 인벤토리 슬롯에 있던 아이템이라면         
					{
						if (draggedItem.itemName != itemToBeSwapped.itemName) // 다른 종류의 소비아이템인 경우 교체하기
						{
							int draggedAmount = draggedItemSlot.amount;
							int swappedAmount = itemSlotToDrop.amount;

							inventory.RemoveItem(draggedItem);
							inventory.RemoveItem(itemToBeSwapped);
	
							inventory.AddItemInSpecificSlot(draggedItem, itemSlotToDrop);
							inventory.AddItemInSpecificSlot(itemToBeSwapped, draggedItemSlot);

							draggedItemSlot.amount = swappedAmount;
							itemSlotToDrop.amount = draggedAmount;

							draggedItemSlot.RenewAmount();
							itemSlotToDrop.RenewAmount();
						}
						else // 같은 종류의 아이템인 경우 merge하기
						{
							if (itemSlotToDrop.amount + draggedItemSlot.amount > draggedItem.maxStack)
							{
								int remainingAmount = itemSlotToDrop.amount + draggedItemSlot.amount - draggedItem.maxStack;

								itemSlotToDrop.amount = draggedItem.maxStack;
								itemSlotToDrop.RenewAmount();

								draggedItemSlot.amount = remainingAmount;
								draggedItemSlot.RenewAmount();
							}
							else
							{
								itemSlotToDrop.amount += draggedItemSlot.amount;
								itemSlotToDrop.RenewAmount();

								inventory.RemoveItem(draggedItem);
							}
						}
					}
				}
			}
		}
	}
    // 드래그 앤 드롭 관련 ----------------------------------------------------------------------------------------------------------------------------------------------------------------------



    // 무기 장착 시켜주는 함수
    public void EquipWeapon(Weapon weapon)
    {
        if(inventory.RemoveItem(weapon)) // 인벤토리에서 아이템 제거에 성공하면
        {
            Weapon previousWeapon;
            if(weaponPanel.AddItem(weapon, out previousWeapon)) // 무기슬롯에 무기 장착을 성공하면
            {
                if(previousWeapon != null) // 이미 전에 무기슬롯에 장착되어있던 무기가 있다면
                {
                    inventory.AddItem(previousWeapon); // 전에 장착되있던 무기를 인벤토리슬롯에 다시 넣어준다
                }             
            }
            else
            {
                inventory.AddItem(weapon); // 무기슬롯에 무기 장착을 실패할 경우 인벤토리슬롯에 무기를 다시 되돌려 놓기
            }
        }
    }

    // 무기 해제 시켜주는 함수
    public void UnequipWeapon(Weapon weapon)
    {
        if(!inventory.IsFull() && weaponPanel.RemoveItem(weapon))
        {
            inventory.AddItem(weapon);
        }
    }

	// 소비아이템 장착 시켜주는 함수
    public void EquipComsummableItem(ItemSlot itemSlot, int amount)
    {
		ConsummableItem previouseConsummableItem;
		int swappedAmount;
		if (consumePanel.AddItem(itemSlot, out previouseConsummableItem, out swappedAmount, amount))
		{
			if (previouseConsummableItem != null)
			{
				inventory.AddItem(previouseConsummableItem, swappedAmount);
			}

			inventory.RemoveItem(itemSlot.Item);
		}
    }

	// 소비아이템 장착해제 시켜주는 함수
    public void UnequipComsummableItem(ItemSlot itemSlot)
    {
		if(!inventory.IsFull() && inventory.AddItem(itemSlot.Item as ConsummableItem, itemSlot.amount))
		{
			consumePanel.RemoveItem(itemSlot.Item as ConsummableItem);
		}
    }


    private void Update()
    {
        if (constructionObject != null)
        {
            LocatePlaceableObject();
        }
    }

    private void LocatePlaceableObject()
    {      
        RaycastHit hit;
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        if (Physics.Raycast(ray, out hit, maxPlacementDistance, groundLayer))
        {
            constructionObject.transform.position = hit.point;
            constructionObject.transform.rotation = Quaternion.FromToRotation(Vector3.up, hit.normal);

            RotatePlaceableObject();
        }

        if (Input.GetMouseButtonDown(0))
        {
            GameManager.Instance.Player.GetComponent<AudioSource>().PlayOneShot(hammeringSFX);

            CampFireSetting campFireSetting = constructionObject.GetComponent<CampFireSetting>();

            if (campFireSetting != null)
            {
                campFireSetting.fireRoot.SetActive(true);
                campFireSetting.coll.enabled = true;
            }
            else
            {
                Collider[] colliders = constructionObject.GetComponents<Collider>();
                foreach (Collider col in colliders)
                {
                    col.enabled = true;
                }
            }

            constructionObject = null;
            mouseWheelRotation = 0.0f;
        }
    }

    private void RotatePlaceableObject()
    {
        mouseWheelRotation += Input.mouseScrollDelta.y;
        if(constructionObject != null)
        {
            constructionObject.transform.Rotate(Vector3.up, mouseWheelRotation * rotationSpeed);
        }
    }
}
