#pragma once

#include "DynamicObject.h"

class Visitor;

class Plane : public DynamicObject {
public:

    void Draw() const override final;

    inline void ChangePlaneY(double dy) { yDirection += dy; }

    void Accept(Visitor* v);

protected:
virtual void DrawBody() const;
virtual void DrawWings() const;
virtual void DrawTail() const;
};

class ColorPlane : public Plane{
public:
    void DrawBody() const override;
    void DrawWings() const override;
    void DrawTail() const override;
};

class BigPlane : public Plane{
public:
    void DrawBody() const override;
    void DrawWings() const override;
    void DrawTail() const override;
};