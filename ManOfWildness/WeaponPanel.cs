using UnityEngine;
using System;
using UnityEngine.UI;

public class WeaponPanel : MonoBehaviour {

    [SerializeField] Transform weaponSlotsParent; // 무기슬롯들의 부모오브젝트의 트랜스폼 컴포넌트
    [SerializeField] EquipmentSlot[] weaponSlots; // 무기슬롯들이 가진 EquipmentSlot 컴포넌트의 배열
    [SerializeField] Text[] durabilityTexts;
    [SerializeField] EquipWeaponToPlayer equipWeaponToPlayer;

	public event Action<ItemSlot> OnRightClickEvenet;
	public event Action<ItemSlot> OnPointerEnterEvent;
	public event Action<ItemSlot> OnPointerExitEvent;
	public event Action<ItemSlot> OnBeginDragEvent;
	public event Action<ItemSlot> OnEndDragEvent;
	public event Action<ItemSlot> OnDragEvent;
	public event Action<ItemSlot> OnDropEvent;

    AudioSource playerAudioSource;
    [SerializeField] AudioClip equippingSFX;

	private void Start()
    {
        for (int i = 0; i < weaponSlots.Length; i++)
        {
            weaponSlots[i].OnRightClickEvenet += OnRightClickEvenet;
			weaponSlots[i].OnRightClickEvenet += OnRightClickEvenet;
			weaponSlots[i].OnPointerEnterEvent += OnPointerEnterEvent;
			weaponSlots[i].OnPointerExitEvent += OnPointerExitEvent;
			weaponSlots[i].OnBeginDragEvent += OnBeginDragEvent;
			weaponSlots[i].OnEndDragEvent += OnEndDragEvent;
			weaponSlots[i].OnDragEvent += OnDragEvent;
			weaponSlots[i].OnDropEvent += OnDropEvent;
		}

        playerAudioSource = GameManager.Instance.Player.GetComponent<AudioSource>();
    }

    private void OnValidate()
    {
        if (!Application.isPlaying)
        {
            weaponSlots = weaponSlotsParent.GetComponentsInChildren<EquipmentSlot>();
            durabilityTexts = weaponSlotsParent.GetComponentsInChildren<Text>();
        }
    }

    public bool AddItem(Weapon weapon, out Weapon previousWeapon) // 무기슬롯에 무기 추가
    {
        for (int i = 0; i < weaponSlots.Length; i++)
        {
            if(weaponSlots[i].EquippableType == weapon.itemType) // 같은타입의 무기슬롯을 찾는다면
            {
                previousWeapon = (Weapon)weaponSlots[i].Item; // 무기슬롯에 기존에 있던 무기 반환, 없다면 null반환
                weaponSlots[i].Item = weapon;
                equipWeaponToPlayer.EquipWeapon(weapon); // 플레이어 무기장착

                playerAudioSource.PlayOneShot(equippingSFX);
                return true;
            }
        }
        previousWeapon = null; // 무기슬롯에 무기 추가 실패한다면 이전 무기에도 null 반환해주기
        return false;
    }

    public bool RemoveItem(Weapon weapon)
    {
        for (int i = 0; i < weaponSlots.Length; i++)
        {
            if (weaponSlots[i].Item == weapon)
            {
                equipWeaponToPlayer.UnequipWeapon(weapon); // 플레이어 무기해제
                weaponSlots[i].Item = null;
                playerAudioSource.PlayOneShot(equippingSFX);
                return true;
            }
        }
        return false;
    }

    private void Update()
    {
        for (int i = 0; i < weaponSlots.Length; i++)
        {
            if (weaponSlots[i].Item != null)
            {
                durabilityTexts[i].enabled = true;
                durabilityTexts[i].text = Mathf.Round((weaponSlots[i].Item as Weapon).durability) + "%";

                if((weaponSlots[i].Item as Weapon).durability <= 0.0f)
                {
                    RemoveItem(weaponSlots[i].Item as Weapon);
                }
            }
            else
            {
                durabilityTexts[i].enabled = false;
            }
        }
    }
}
