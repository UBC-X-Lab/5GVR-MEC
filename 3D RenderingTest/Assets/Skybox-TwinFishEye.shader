Shader "Skybox/TwinFishEye" {
Properties {
    _Tint ("Tint Color", Color) = (.5, .5, .5, .5)
    [Gamma] _Exposure ("Exposure", Range(0, 8)) = 1.0
    [NoScaleOffset] _MainTex ("Spherical  (HDR)", 2D) = "grey" {}
}

SubShader {
    Tags { "Queue"="Background" "RenderType"="Background" "PreviewType"="Skybox" }
    Cull Off ZWrite Off

    Pass {

        CGPROGRAM
        #pragma vertex vert
        #pragma fragment frag
        #pragma target 2.0

        #include "UnityCG.cginc"

        sampler2D _MainTex;
        float4 _MainTex_TexelSize;
        half4 _MainTex_HDR;
        half4 _Tint;
        half _Exposure;

        inline float2 ToRadialCoords(float3 coords)
        {
            float3 normalizedCoords = normalize(coords);
            float2 lensCenter;
            float2 lensRadius;
            if (normalizedCoords.z > 0.0) {
                lensCenter = float2(4575.319 / 6080, 1521.183 / 3040);
                lensRadius = float2(1430.017 / 6080, 1430.017 / 3040);
            } else {
                lensCenter = float2(1530.073 / 6080, 1515.421 / 3040);
                lensRadius = float2(1425.675 / 6080, 1425.675 / 3040);
                normalizedCoords.x = -normalizedCoords.x;
            }
            float theta = atan2(normalizedCoords.y, normalizedCoords.x);
            //float r = sqrt(1 - normalizedCoords.z * normalizedCoords.z);
            float r = acos(abs(normalizedCoords.z)) / (UNITY_PI / 2) * 180/186;
            return lensCenter + lensRadius * float2(r * cos(theta), r * sin(theta));
        }

        struct appdata_t {
            float4 vertex : POSITION;
            UNITY_VERTEX_INPUT_INSTANCE_ID
        };

        struct v2f {
            float4 vertex : SV_POSITION;
            float3 texcoord : TEXCOORD0;
            UNITY_VERTEX_OUTPUT_STEREO
        };

        v2f vert (appdata_t v)
        {
            v2f o;
            UNITY_SETUP_INSTANCE_ID(v);
            UNITY_INITIALIZE_VERTEX_OUTPUT_STEREO(o);
            o.vertex = UnityObjectToClipPos(v.vertex);
            o.texcoord = v.vertex.xyz;
            return o;
        }

        fixed4 frag (v2f i) : SV_Target
        {
            float2 tc = ToRadialCoords(i.texcoord);
            half4 tex = tex2D (_MainTex, tc);
            half3 c = DecodeHDR (tex, _MainTex_HDR);
            c = c * _Tint.rgb * unity_ColorSpaceDouble.rgb;
            c *= _Exposure;
            return half4(c, 1);
        }
        ENDCG
    }
}

Fallback Off

}
