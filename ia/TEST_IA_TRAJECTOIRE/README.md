###### Algorithme de propagation de la récompense

T = territoire

$Ve =$ Valeur d'état

$(R(x),R(y)) =$ Coordonnées de la récompense

ℤ = Valeur de la récompense

$γ = 0.90$

$∀\ Ve ≠ ℤ, Ve = γVe'$

$∀\ état ∈ T$, $Ve ≠ 1$, $∃\ un ensemble de Ve tel que${ 

//Surface gauche haut 

$Pour\ y ≤ R(y)\ et\ pour\ x ≤ R(x)$

$( R(y) - y , R(x) - x  ) = γ^{x+y}$

//Surface droite haut 

$Pour\ y ≤ R(y)\ et\ pour\ x ≤ argmax(x)-R(x)$

$( R(y) - y , R(x) + x  ) = γ^{x+y}$

//Surface gauche bas

$Pour\ y ≤ argmax(y) - R(y)\ et\ pour\ x ≤ R(x)$

$( R(y) + y , R(x) - x  ) = γ^{x+y}$

//Surface droite bas

$Pour\ y ≤ argmax(y) - R(y)\ et\ pour\ x ≤ argmax(x) - R(x)$

$( R(y) + y , R(x) + x  ) = γ^{x+y}$

}
