// Dot(Vector3, Vector3): Vector3同士の内積
// Cross(Vector3, Vector3): Vector3同士の外積

// レイと三角形の交差判定
//   交差する場合:   Vector3(t, u, v) 
//   交差しない場合: std::nullopt 
// が戻り値となる。
std::optional<Vector3> Intersect(
    Vector3 o,  // レイの原点
    Vector3 d,  // レイの向き
    Vector3 v0, // 三角形の頂点0
    Vector3 v1, // 三角形の頂点1
    Vector3 v2, // 三角形の頂点2
) {
    // 微小な定数([Möller97] での値)
    constexpr float kEpsilon = 1e-6f;

    Vector3 e1 = v1 - v0;
    Vector3 e2 = v2 - v0;

    Vector3 alpha = Cross(d, e2);
    float det = Dot(e1, alpha);

    // 三角形に対して、レイが平行に入射するような場合 det = 0 となる。
    // det が小さすぎると 1/det が大きくなりすぎて数値的に不安定になるので
    // det ≈ 0 の場合は交差しないこととする。
    if (-kEpsilon < det && det < kEpsilon) {
        return std::nullopt;
    }

    float invDet = 1.0f / det;
    Vector3 r = o - v0;
    
    // u が 0 <= u <= 1 を満たしているかを調べる。
    float u = Dot(alpha, r) * invDet;
    if (u < 0.0f || u > 1.0f) {
        return std::nullopt;
    }

    Vector3 beta = Cross(r, e1);

    // v が 0 <= v <= 1 かつ u + v <= 1 を満たすことを調べる。
    // すなわち、v が 0 <= v <= 1 - u をみたしているかを調べればOK。
    float v = Dot(d, beta) * invDet;
    if (v < 0.0f || u + v > 1.0f) {
        return std::nullopt;
    }

    // t が 0 <= t を満たすことを調べる。
    float t = Dot(e2, beta) * invDet;
    if (t < 0.0f) {
        return std::nullopt;
    }

    // 交差した！！！！
    return Vector3(t, u, v);
}