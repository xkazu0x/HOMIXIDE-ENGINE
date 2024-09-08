#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::string filepath) :
    m_vao(), m_vbo(), m_vertices(vertices), m_texture(nullptr) {
    m_texture = LoadTexture(filepath);

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv)));

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);

    if (m_texture != nullptr) {
        delete m_texture;
    }
}

void Mesh::Draw(unsigned int mode) {
    if (m_texture != nullptr) {
        m_texture->Bind();
    }

    glBindVertexArray(m_vao);
    glDrawArrays(mode, 0, static_cast<GLsizei>(m_vertices.size()));
}
