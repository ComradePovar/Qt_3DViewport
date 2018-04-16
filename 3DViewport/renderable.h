#ifndef RENDERABLE_H
#define RENDERABLE_H

class Renderable {
private:
	bool m_hidden = false;
public:
	bool isHidden() const { return m_hidden; }
	void hide() { m_hidden = true; }
	void unhide() { m_hidden = false; }
	virtual void render() = 0;
};


#endif