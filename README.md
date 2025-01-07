# 第三人称射击游戏

## 关键词

+ Unreal Engine 5
+ c++
+ GAS -- Gameplay Ability System
+ 仿 Lyra 动画
+ UE 行为树
+ 局域网联机 -- 开发中



此库是个人对 UE5 的一个入门demo, 所以肯定会有一些幼稚的做法, 大佬轻喷

源码在 --> https://github.com/aolixin/TPSGame



## Gameplay 部分

Lyra 的 Gameplay 主要是 Game Feature + Game Modular 这么一个思路

Game Feature 的话可以看这个 --> https://www.bilibili.com/video/BV1j34y1B7Nf/?vd_source=f5a60e427f20c3013ba8ece910e0d0ec

这里 Lyra 用的是一个叫 Game Modular 的一个框架, 这个框架貌似就是对 UE 本身的 Gameplay 再封了一层, 它对所有涉及到的引擎原有模块做出继承, 充当了项目和引擎之间的缓冲带.

<img src="img\gameplay1.png" alt="image-20250107102856482" style="zoom:100%;" />

但是我想保证项目尽可能简单, 所以就不用这个了, 直接用 UE 本身的 gameplay 框架

用到哪部分就重写哪部分的逻辑

<img src="img\gameplay2.png" alt="image-20250107102856482" style="zoom:100%;" />

## 动画部分

主要参考 Lyra 的动画, 实现分层的思想

<img src="img\donghua1.png" alt="image-20250107102856482" style="zoom:100%;" />

1. 整体上, 我们的 Character 直接使用 ABP_TPSCharacter
2. ABP_TPSCharacter, ABP_TPSLayerBase 均实现 ALI_AnimLayerInterface
3. ALI_AnimLayerInterface 定义动画的各层
4. ABP_TPSCharacter 实现状态机
5. ABP_TPSLayerBase 中实现各个层的效果
6. ABP_PistolLayer 填入各个层具体的参数
7. 然后在运行时, 用 Link Anim Class Layers 将 ABP_TPSCharacter 替换为  ABP_TPSLayerBase 

<img src="img\donghua2.png" alt="image-20250107102856482" style="zoom:100%;" />





## 玩家输入 & GAS

GAS 网上有很多讲的非常棒的博客, 这里就不列出具体的

关于 GAS 的使用, 也是参考了 Lyra 做的简化版

主要思路是这样:

IMC 定义 输入 --> IA 的映射

Input Config 定义 IA --> Gameplay Tag 的映射

Ability Set 定义 Gameplay Tag --> GA 的映射

GA 定义具体的行为



<img src="img\gas1.png" alt="image-20250107102856482" style="zoom:100%;" />



<img src="img\gas2.png" alt="image-20250107102856482" style="zoom:67%;" />



<img src="img\gas3.png" alt="image-20250107102856482" style="zoom:67%;" />

<img src="img\gas4.png" alt="image-20250107102856482" style="zoom:100%;" />



其中 Input Config 和 Ability Set 定义如下

```
USTRUCT(BlueprintType)
struct FTPSInputAction
{
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<const UInputAction> InputAction = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FGameplayTag InputTag;
};

UCLASS()
class TPS_API UTPSInputConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FTPSInputAction> NativeInputActions;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FTPSInputAction> AbilityInputActions;
};
```





```
USTRUCT(BlueprintType)
struct FTPSAbilitySet_GameplayAbility
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UTPSGameplayAbility> Ability = nullptr;

    UPROPERTY(EditDefaultsOnly)
    int32 AbilityLevel = 1;

    UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
    FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FTPSAbilitySet_GrantedHandles
{
    GENERATED_BODY()

public:
    void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);

protected:
    UPROPERTY()
    TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

    UPROPERTY()
    TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

    UPROPERTY()
    TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};

UCLASS()
class TPS_API UTPSAbilitySet : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UTPSAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    void GiveToAbilitySystem(UTPSAbilitySystemComponent* ASC, FTPSAbilitySet_GrantedHandles* OutGrantedHandles,
                             UObject* SourceObject = nullptr) const;

    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
    TArray<FTPSAbilitySet_GameplayAbility> GrantedGameplayAbilities;
};
```



## AI

这里比较简单, 直接是参考 UE 官方示例, 改了改 --> https://dev.epicgames.com/documentation/zh-cn/unreal-engine/behavior-tree-in-unreal-engine---quick-start-guide





## 局域网

-- todo





## 效果展示

<img src="img\xiaoguo1.png" alt="image-20250107102856482" style="zoom:67%;" />
