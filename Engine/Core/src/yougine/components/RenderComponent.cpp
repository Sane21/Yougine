﻿#include "RenderComponent.h"
#include "./../managers/RenderManager.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tinygltf/tiny_gltf.h"

namespace yougine::components
{
    RenderComponent::RenderComponent() : Component(managers::ComponentName::kRender), program(0), vao(0)
    {
        GLuint program, vao;
        program = yougine::managers::RenderManager::ShaderInitFromFilePath(
            "./Resource/shader/test.vert", "./Resource/shader/test.frag");
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        this->SetProgram(program);
        this->SetVao(vao);

        //シェーダに値を渡す
        auto vertexShader_PositionAttribute = glGetAttribLocation(program, "position");

        tinygltf::Model model;
        tinygltf::TinyGLTF loader;
        std::string err, warn;
        bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, "./Resource/Mesh/test_model/testmodel.gltf");
        std::cout << "scene length" << model.scenes.size() << std::endl;
        auto scene = model.scenes[0];
        auto nodeindex = scene.nodes[0]; //シーンの参照しているのノード（本当は複数あるパターンにも対応すべき）
        auto node = model.nodes[nodeindex];
        auto mesh = model.meshes[node.mesh];
        auto position_index = mesh.primitives[0].attributes["POSITION"]; //accessorのインデックス
        auto indices_index = mesh.primitives[0].indices; //accessorのインデックス
        auto position_accessor = model.accessors[position_index];

        auto buffer_views = model.bufferViews;

        auto position_buffer_view = buffer_views[position_accessor.bufferView];
        auto position_buffer = model.buffers[position_buffer_view.buffer];
        const float* positions = reinterpret_cast<const float*>(&position_buffer.data[position_buffer_view.byteOffset +
            position_accessor.byteOffset]);
        std::cout << "position buffer data" << std::endl;
        //頂点座標をvertex_vectorに追加
        this->vertex_vector = {};
        for (size_t i = 0; i < position_accessor.count; ++i)
        {
            // std::cout << i << "番目 : " << "[" << positions[i * 3 + 0] << "," << positions[i * 3 + 1] << "," << positions[
            //     i * 3 + 2] << "]" << std::endl;
            Vertex v = {positions[i * 3 + 0], positions[i * 3 + 1], positions[i * 3 + 2], 1};
            this->vertex_vector.push_back(v);
        }
        auto indices_accessor = model.accessors[indices_index];
        auto indices_buffer_view = buffer_views[indices_accessor.bufferView];
        auto indices_buffer = model.buffers[indices_buffer_view.buffer];
        const unsigned short* indices_data_fromgltf = reinterpret_cast<const unsigned short*>(&indices_buffer.data[
            indices_buffer_view.byteOffset + indices_accessor.byteOffset]);
        std::cout << "index buffer data" << std::endl;
        //インデックスをindex_vectorに追加
        this->index_vector = {};
        for (size_t i = 0; i < indices_accessor.count; ++i)
        {
            // std::cout << i << "番目 : " << "[" << indices_data_fromgltf[i] << "]" << std::endl;
            this->index_vector.push_back(indices_data_fromgltf[i]);
        }

        std::cout << std::endl;
        std::cout << "buffer num " << model.buffers[0].data.size() << std::endl;

        auto positioncomponenttype = position_accessor.componentType;

        std::cout << "scene node : " << node.mesh << std::endl;

        auto position_point_count = position_accessor.count;
        //頂点バッファを作成
        GLuint vertexBuffer;
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        auto vertex = this->vertex_vector;
        glBufferData(GL_ARRAY_BUFFER, position_point_count * sizeof(Vertex), vertex.data(), GL_STATIC_DRAW);

        // //インデックスバッファ
        GLuint elementBuffer;
        glGenBuffers(1, &elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        auto indices = this->index_vector;
        auto indeicesSize = indices.size()*sizeof(indices[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeicesSize, indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(vertexShader_PositionAttribute);
        glVertexAttribPointer(vertexShader_PositionAttribute, 4, GL_FLOAT, GL_FALSE, 0, 0);
        this->draw_point_count = indices_accessor.count;
    }

    void RenderComponent::SetProgram(GLuint program)
    {
        this->program = program;
    }

    void RenderComponent::SetVao(GLuint vao)
    {
        this->vao = vao;
    }

    GLuint RenderComponent::GetProgram() const
    {
        return program;
    }

    GLuint RenderComponent::GetVao() const
    {
        return vao;
    }

    std::vector<Vertex> RenderComponent::GetVertexVector() const
    {
        return vertex_vector;
    }

    void RenderComponent::SetVertexVector(const std::vector<Vertex>& vertex_vector)
    {
        this->vertex_vector = vertex_vector;
    }

    std::vector<GLuint> RenderComponent::GetIndexVector() const
    {
        return index_vector;
    }

    void RenderComponent::SetIndexVector(const std::vector<GLuint>& index_vector)
    {
        this->index_vector = index_vector;
    }
}
