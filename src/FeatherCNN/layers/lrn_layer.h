//Tencent is pleased to support the open source community by making FeatherCNN available.

//Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.

//Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
//in compliance with the License. You may obtain a copy of the License at
//
//https://opensource.org/licenses/BSD-3-Clause
//
//Unless required by applicable law or agreed to in writing, software distributed
//under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//CONDITIONS OF ANY KIND, either express or implied. See the License for the
//specific language governing permissions and limitations under the License.

#pragma once

#include "../feather_simple_generated.h"
#include "../layer.h"

namespace feather
{
class LRNLayer : public Layer
{
    public:
        LRNLayer(const LayerParameter* layer_param, const RuntimeParameter<float>* rt_param);
        int Forward();
        int Init();
    private:
        //int CompSquare();
        int AcrossChannels();
        size_t local_size;
        float alpha;
        float alpha_over_size;
        float beta;
        float k;

        size_t _pre_pad;
        float* _square;
        float* _square_sum;

        float* _scale_data;
        float* _padded_sqr_data;
};
};
