using System;
using UnityEngine;

public class ConsumePanel : MonoBehaviour {

    [SerializeField] Transform consumeSlotsParent; // 소모슬롯들의 부모오브젝트의 트랜스폼 컴포넌트
    public EquipmentSlot[] consumeSlots; // 소모슬롯들이 가진 EquipmentSlot 컴포넌트의 배열

	public EquipArrowToPlayer equipArrowToPlayer;

	public event Action<ItemSlot> OnRightClickEvenet;
	public event Action<ItemSlot> OnPointerEnterEvent;
	public event Action<ItemSlot> OnPointerExitEvent;
	public event Action<ItemSlot> OnBeginDragEvent;
	public event Action<ItemSlot> OnEndDragEvent;
	public event Action<ItemSlot> OnDragEvent;
	public event Action<ItemSlot> OnDropEvent;

    PlayerState playerState;
    AudioSource playerAudioSource;
    [SerializeField] AudioClip eatingSFX; 

	private void Start()
    {
        for (int i = 0; i < consumeSlots.Length; i++)
        {
            consumeSlots[i].OnRightClickEvenet += OnRightClickEvenet;
			consumeSlots[i].OnRightClickEvenet += OnRightClickEvenet;
			consumeSlots[i].OnRightClickEvenet += OnRightClickEvenet;
			consumeSlots[i].OnPointerEnterEvent += OnPointerEnterEvent;
			consumeSlots[i].OnPointerExitEvent += OnPointerExitEvent;
			consumeSlots[i].OnBeginDragEvent += OnBeginDragEvent;
			consumeSlots[i].OnEndDragEvent += OnEndDragEvent;
			consumeSlots[i].OnDragEvent += OnDragEvent;
			consumeSlots[i].OnDropEvent += OnDropEvent;
		}

        playerState = GameManager.Instance.Player.GetComponent<PlayerState>();
        playerAudioSource = GameManager.Instance.Player.GetComponent<AudioSource>();
    }

    private void OnValidate()
    {
        if(!Application.isPlaying)
        {
            consumeSlots = consumeSlotsParent.GetComponentsInChildren<EquipmentSlot>();
        }
    }

    public bool AddItem(ItemSlot itemSlot, out ConsummableItem previousConsummableItem, out int swappedAmount, int amount)
    {
        EquipmentSlot emptySlot = null;
        for (int i = 0; i < consumeSlots.Length; i++)
        {
            if(consumeSlots[i].EquippableType == (itemSlot.Item as ConsummableItem).itemType)
            {
                if(consumeSlots[i].Item == null)
                {
                    emptySlot = consumeSlots[i];
					emptySlot.amount += amount;
					emptySlot.RenewAmount();
                    break;
                }
            }
        }

        if(emptySlot == null)
        {
            for (int i = 0; i < consumeSlots.Length; i++)
            {
                if (consumeSlots[i].EquippableType == (itemSlot.Item as ConsummableItem).itemType)
                {
                    if ((itemSlot.Item as ConsummableItem).itemType == ItemTypes.Arrow)
                    {
                        if(consumeSlots[4].Item == null)
                        {
                            previousConsummableItem = (ConsummableItem)consumeSlots[i].Item;
                            swappedAmount = consumeSlots[i].amount;

                            consumeSlots[i].Item = itemSlot.Item;
                            consumeSlots[i].amount = amount;
                            consumeSlots[i].RenewAmount();

                            equipArrowToPlayer.EquipArrow(itemSlot.Item as ConsummableItem);
                        }
                        else
                        {
                            if(itemSlot.Item.itemName == consumeSlots[4].Item.itemName) // 같은종류의 화살인 경우
                            {
                                if(itemSlot.Item.maxStack > itemSlot.amount + consumeSlots[4].amount)
                                {
                                    consumeSlots[4].amount += itemSlot.amount;
                                    previousConsummableItem = null;
                                    swappedAmount = 0;
                                }
                                else
                                {
                                    int remainingArrow = itemSlot.amount + consumeSlots[4].amount - itemSlot.Item.maxStack;
                                    consumeSlots[4].amount = itemSlot.Item.maxStack;                                  
                                    previousConsummableItem = itemSlot.Item as ConsummableItem;
                                    swappedAmount = remainingArrow;

                                    itemSlot.Item = null;
                                    itemSlot.amount = 0;
                                }

                                consumeSlots[4].RenewAmount();
                            }
                            else
                            {
                                previousConsummableItem = (ConsummableItem)consumeSlots[i].Item;
                                swappedAmount = consumeSlots[i].amount;

                                consumeSlots[i].Item = itemSlot.Item;
                                consumeSlots[i].amount = amount;
                                consumeSlots[i].RenewAmount();

                                equipArrowToPlayer.UnequipArrow();
                                equipArrowToPlayer.EquipArrow(itemSlot.Item as ConsummableItem);
                            }
                        }
                    }
                    else
                    {
                        previousConsummableItem = (ConsummableItem)consumeSlots[i].Item;
                        swappedAmount = consumeSlots[i].amount;

                        consumeSlots[i].Item = itemSlot.Item;
                        consumeSlots[i].amount = amount;
                        consumeSlots[i].RenewAmount();
                    }

                    return true;
                }
            }
            previousConsummableItem = null;
			swappedAmount = 0;
			return false;
        }
        else
        {
            previousConsummableItem = emptySlot.Item as ConsummableItem;
			swappedAmount = emptySlot.amount;
			emptySlot.Item = itemSlot.Item;
			
            if ((itemSlot.Item as ConsummableItem).itemType == ItemTypes.Arrow)
            {
                equipArrowToPlayer.EquipArrow(itemSlot.Item as ConsummableItem);
            }
			return true;
        }
    }

    public bool RemoveItem(ConsummableItem consummableItem)
    {
        for (int i = 0; i < consumeSlots.Length; i++)
        {
            if (consumeSlots[i].Item == consummableItem)
            {
				if (consummableItem.itemType == ItemTypes.Arrow)
				{
					equipArrowToPlayer.UnequipArrow();
				}

				consumeSlots[i].amount = 0;
				consumeSlots[i].RenewAmount();
				consumeSlots[i].Item = null;
                return true;
            }
        }
        return false;
    }

    public void AddItemInSpecificSlot(ConsummableItem consummableItem, ItemSlot itemSlot)
    {
        itemSlot.Item = consummableItem;

        if(consummableItem.itemType == ItemTypes.Arrow)
        {
            equipArrowToPlayer.UnequipArrow();
            equipArrowToPlayer.EquipArrow(consummableItem);
        }

		itemSlot.RenewAmount();
    }

    public void ConsumeArrow()
    {
        consumeSlots[4].amount--;
        consumeSlots[4].RenewAmount();

        if (consumeSlots[4].amount == 0)
        {
            equipArrowToPlayer.UnequipArrow();
            consumeSlots[4].Item = null;
        }

    }

    private void Update()
    {
        if(Input.GetKeyDown(KeyCode.Alpha1))
        {
            if(consumeSlots[0].Item != null)
            {
                ConsummableItem item = consumeSlots[0].Item as ConsummableItem;
                playerState.life += item.plusLife;
                playerState.thirst += item.plusThirst;
                playerState.hunger += item.plusHunger;

                playerAudioSource.PlayOneShot(eatingSFX);

				consumeSlots[0].amount--;
				consumeSlots[0].RenewAmount();

				if(consumeSlots[0].amount == 0)
				{
					consumeSlots[0].Item = null;
				}
            }
        }

        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            if (consumeSlots[1].Item != null)
            {
                ConsummableItem item = consumeSlots[1].Item as ConsummableItem;
                playerState.life += item.plusLife;
                playerState.thirst += item.plusThirst;
                playerState.hunger += item.plusHunger;

                playerAudioSource.PlayOneShot(eatingSFX);

				consumeSlots[1].amount--;
				consumeSlots[1].RenewAmount();

				if (consumeSlots[1].amount == 0)
				{
					consumeSlots[1].Item = null;
				}
			}
        }

        if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            if (consumeSlots[2].Item != null)
            {
                ConsummableItem item = consumeSlots[2].Item as ConsummableItem;
                playerState.life += item.plusLife;
                playerState.thirst += item.plusThirst;
                playerState.hunger += item.plusHunger;

                playerAudioSource.PlayOneShot(eatingSFX);

				consumeSlots[2].amount--;
				consumeSlots[2].RenewAmount();

				if (consumeSlots[2].amount == 0)
				{
					consumeSlots[2].Item = null;
				}
			}
        }

        if (Input.GetKeyDown(KeyCode.Alpha4))
        {
            if (consumeSlots[3].Item != null)
            {
                ConsummableItem item = consumeSlots[3].Item as ConsummableItem;
                playerState.life += item.plusLife;
                playerState.thirst += item.plusThirst;
                playerState.hunger += item.plusHunger;

                playerAudioSource.PlayOneShot(eatingSFX);

				consumeSlots[3].amount--;
				consumeSlots[3].RenewAmount();

				if (consumeSlots[3].amount == 0)
				{
					consumeSlots[3].Item = null;
				}
			}
        }
    }
}
