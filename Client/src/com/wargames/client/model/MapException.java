package com.wargames.client.model;

/**
 * Generic Map Exception to hold all errors in the map.
 * @author Clinton
 *
 */
public class MapException extends Exception {

	/**
	 * Generated serial version.
	 */
	private static final long serialVersionUID = 1L;

	public MapException(String message)
	{
		super(message);
	}
}
