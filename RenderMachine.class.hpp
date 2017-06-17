#ifndef RENDER_MACHINE_CLASS_H
# define RENDER_MACHINE_CLASS_H

# include <string>
# include <iostream>
# include "IPrintable.class.hpp"

class RenderMachine {
public:
	RenderMachine(void);
	RenderMachine(RenderMachine const & src);
	~RenderMachine(void);

	RenderMachine & operator=(RenderMachine const & rhs);

	void	renderAll(void);

private:
	IPrintable		**_tab;
	unsigned int	_amount;
};

#endif
