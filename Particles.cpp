#include "VBO.h"
#include "Texture.h"
#include "GameObject.h"
#include "game.h"
#include "Particles.h"

Particle::Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 scale, glm::vec4 color, float life) {
    float random = ((rand() % 100) - 50) / 50.0f;
    float randColor = 0.5f + ((rand() % 100) / 100.0f);

    this->position = glm::vec3(position + random);
    this->velocity = glm::vec3(velocity);
    this->scale = glm::vec3(scale);

    this->color = glm::vec4(color);
    this->life = life;
}

void Particle::draw(Game* g, VAO* vao, Texture* texture, Camera* camera) {
    g->shaders[3]->Activate();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glUniform2f(glGetUniformLocation(g->shaders[3]->ID, "offset"), position.x, position.y);
    glUniform4f(glGetUniformLocation(g->shaders[3]->ID, "color"), color.x, color.y, color.z, color.w);
    glUniformMatrix4fv(glGetUniformLocation(g->shaders[3]->ID, "proj"), 1, GL_FALSE, glm::value_ptr(g->cameras[0]->cameraMatrix));
    texture->Bind();
    vao->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao->Unbind();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

ParticleSystem::ParticleSystem(Texture* texture)
{
    this->init();
    this->texture = texture;
    this->amount = amount;
}

void ParticleSystem::update(Game* g) {
    for (Particle*& p : this->particles) {
        if (p == nullptr) continue;
        float dt = g->deltaTime();
        p->life -= dt; //dt reduces the life of each particle gradually

        if (p->life <= 0.0f) {
            delete p;
            p = nullptr;
            continue;
        }

        //if the particle is still alive:
        p->position -= p->velocity * dt;
        p->color.a -= dt * 2.5f;
        
        bool collide = g->balls[0]->circintersects(p->position, g->paddles[0]->position, 3.0f);
        bool collide2 = g->balls[0]->circintersects(p->position, g->paddles[1]->position, 3.0f);

        if (collide || collide2) {
            p->velocity = -p->velocity + rand() / 250.0f;
        }
    }
    draw(g);
}

void ParticleSystem::draw(Game* g) {
    for (Particle*& particle : this->particles) 
        if (particle != nullptr) particle->draw(g, &particleVAO, texture, g->cameras[0]);
}

void ParticleSystem::init() {
    VBO particleVBO;

    float particleQuad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    this->particleVAO.Bind();
    particleVBO.Bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleQuad), particleQuad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    this->particleVAO.Bind();
}

void ParticleSystem::spawn(Game* g, glm::vec3 position, glm::vec3 velocity, glm::vec3 scale, glm::vec4 color, float life) {
    Particle* newP = new Particle(position, velocity, scale, color, life);
    for (Particle*& p : this->particles) {
        if (p == nullptr) {
            p = newP;
            return;
        }
    }

    this->particles.push_back(newP);
}